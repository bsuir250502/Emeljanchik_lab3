#include <stdio.h>
#include <stdlib.h>
#define n_max_number 5
#define PLATE_NUMBER 10
struct car_list {
	char number_plate[PLATE_NUMBER];
	struct car_list *prev;
};
struct city_parking {
	int total_number_of_places;
	int number_of_free_places;
	struct car_list *standing_car;
	struct car_list *waiting_car;
	struct city_parking *prev;
};
struct car_list *free_list (car_list *must_be_free1, int number_on_parking1) {
	car_list *required3;
	int i=0, j;
	if (must_be_free1!=NULL) {
		required3=must_be_free1;
		while (required3->prev!=NULL) {
			i++;
			required3=required3->prev;
		}
		free (required3);
		while (i>1) {
			required3=must_be_free1;
			j=1;
			while (j<i) {
				j++;
				required3=required3->prev;
			}
			free (required3);
			i--;
		}
	}
	return must_be_free1;
}
struct city_parking free_all (city_parking *must_be_free2, int number_of_parking2) {
	city_parking *required;
	int i=0, j;
	required=must_be_free2;
	free_list (required->standing_car, number_of_parking2);
	free_list (required->waiting_car, number_of_parking2);
	while (required->prev!=NULL) {
		i++;
		required=required->prev;
		free_list (required->standing_car, number_of_parking2);
		free_list (required->waiting_car, number_of_parking2);
	}
	while (i>0) {
		required=must_be_free2;
		j=1;
		while (j<i) {
			j++;
			required=required->prev;
		}
		free (required->prev);
		i--;
	}
	free (required);
	return *must_be_free2;
}
struct city_parking add_car (int number_of_parking3, city_parking *main_city_parking3) {
	city_parking *required;
	car_list *required1;
	int j=1;
	required=main_city_parking3;
	while (j<number_of_parking3) {
		j++;
		required=required->prev;
	}
	if (required->standing_car==NULL) {
		if (!(required->standing_car=(car_list *)malloc(sizeof(car_list)))) {
			free_all (main_city_parking3, number_of_parking3);
			printf ("\nFatality error:\nProgram will close...");		
			number_of_parking3=0;
			return *main_city_parking3;
		}
		printf ("\nPlease enter plate number: ");
		fgets (required->standing_car->number_plate, PLATE_NUMBER, stdin);
		required->standing_car->prev=NULL;
		return *main_city_parking3;
	}
	else {
		if (required->number_of_free_places==0) {
			if (required->waiting_car==NULL) {
				if (!(required->waiting_car=(car_list *)malloc(sizeof(car_list)))) {
					free_all (main_city_parking3, number_of_parking3);
					printf ("\nFatality error:\nProgram will close...");		
					number_of_parking3=0;
					return *main_city_parking3;
				}
				printf ("\nPlease enter plate number: ");
				fgets (required->waiting_car->number_plate, PLATE_NUMBER, stdin);
				required->waiting_car->prev=NULL;
			}
			else {
				required1=required->waiting_car;
				while (required1->prev!=NULL)
					required1=required1->prev;
				if (!(required1->prev=(car_list *)malloc(sizeof(car_list)))) {
					free_all (main_city_parking3, number_of_parking3);
					printf ("\nFatality error:\nProgram will close...");		
					number_of_parking3=0;
					return *main_city_parking3;
				}
				printf ("\nPlease enter plate number: ");
				fgets (required1->prev->number_plate, PLATE_NUMBER, stdin);
				required1->prev->prev=NULL;
			}
			return *main_city_parking3;
		}
		else {
			required->number_of_free_places--;
			required1=required->standing_car;
			while (required1->prev!=NULL)
				required1=required1->prev;
			if (!(required1->prev=(car_list *)malloc(sizeof(car_list)))) {
				free_all (main_city_parking3, number_of_parking3);
				printf ("\nFatality error:\nProgram will close...");		
				number_of_parking3=0;
				return *main_city_parking3;
			}
			printf ("\nPlease enter plate number: ");
			fgets (required1->prev->number_plate, PLATE_NUMBER, stdin);
			required1->prev->prev=NULL;
			return *main_city_parking3;
		}
	}
}
struct city_parking del_car (int number_of_parking4, city_parking *main_city_parking4) {
	city_parking *required;
	car_list *required1;
	required=main_city_parking4;
	int j=1;
	while (j<number_of_parking4) {
		j++;
		required=required->prev;
	}
	if (required->standing_car==NULL) {
		printf ("\nError:\nNoone car on this parking!");
		return *main_city_parking4;
	}
	if (required->waiting_car!=NULL) {
		for (j=0; j<PLATE_NUMBER; j++) {
			required->standing_car->number_plate[j]=required->waiting_car->number_plate[j];
			if (required->waiting_car->number_plate[j]=='\0')
				break;
		}
		required1=required->standing_car;
		while (required1->prev!=NULL)
			required1=required1->prev;
		required1->prev=required->standing_car;
		required1=required->standing_car->prev;
		required->standing_car->prev=NULL;
		required->standing_car=required1;
		required1=required->waiting_car->prev;
		free (required->waiting_car);
		required->waiting_car=required1;
		return *main_city_parking4;
	}
	required1=required->standing_car->prev;
	free (required->standing_car);
	required->standing_car=required1;
	return *main_city_parking4;
}
struct city_parking enter_information_about_parking (city_parking *main_city_parking5, int number_of_parking5) {
	char char_n[n_max_number];
	int n;
	city_parking *required;
	required=main_city_parking5;
	while (required->prev!=NULL)
		required=required->prev;
	while (1) {
		printf ("Please enter information about car parking:\nPlease enter total number of places on parking: ");
		fgets (char_n, n_max_number, stdin);
		required->total_number_of_places=strtol (char_n, NULL, 10);
		if (required->total_number_of_places<=0)
			printf ("\nError:\nBad number, please try again...");
		else break;
	}
	while (1) {
		printf ("\nPlease enter the number of free places on parking: ");
		fgets (char_n, n_max_number, stdin);
		required->number_of_free_places=strtol (char_n, NULL, 10);
		if (required->number_of_free_places<0 ||
			required->number_of_free_places>required->total_number_of_places)
			printf ("\nError:\nBad number, please try again...");
		else break;
	}
	n=required->total_number_of_places-required->number_of_free_places;
	while (n-->0) {
		if (number_of_parking5==0)
			break;
		add_car (number_of_parking5, main_city_parking5);
	}
	return *main_city_parking5;
}
struct city_parking add_city_parking (city_parking *main_city_parking6, int number_of_parking6) {
	city_parking *required;
	required=main_city_parking6;
	while (required->prev!=NULL)
		required=required->prev;
	if (!(required->prev=(city_parking *)malloc(sizeof(city_parking)))) {
		printf ("\nError:\nNot enough memory...");
		number_of_parking6=0;
		free_all (main_city_parking6, number_of_parking6);
		return *main_city_parking6;
	}
	required->prev->prev=NULL;
	required->prev->standing_car=NULL;
	required->prev->waiting_car=NULL;
	enter_information_about_parking (main_city_parking6, number_of_parking6);
	return *main_city_parking6;
}
int main() {
	struct city_parking *city_parking_pointer;
	int number_of_parking=1;
	int number_of_parking2;
	char char_n[n_max_number];
	if (!(city_parking_pointer=(city_parking *)malloc(sizeof(city_parking)))) {
		printf ("\nFatality error:\nProgram will close...");
		return 0;
	}
	city_parking_pointer->prev=NULL;
	city_parking_pointer->standing_car=NULL;
	city_parking_pointer->waiting_car=NULL;
	enter_information_about_parking (city_parking_pointer, number_of_parking);
	if (number_of_parking==0)
		return 0;
	while (1) {
		printf ("\nEnter what you want:\nIf add car - +.\nIf delete car - -.\nIf add parking - a.\nIf quit - q: ");
		fgets (char_n, n_max_number, stdin);
		if (char_n[0]=='+') {
			while (1) {
				printf ("\nPlease enter what parking you want (from 1 to %d): ", number_of_parking);
				fgets (char_n, n_max_number, stdin);
				number_of_parking2=strtol (char_n, NULL, 10);
				if (number_of_parking2<=0 || number_of_parking2>number_of_parking)
					printf ("\nError:\nBad number, please try again...");
				else break;
			}
			add_car (number_of_parking2, city_parking_pointer);
			if (number_of_parking==0) {
				return 0;
			}
		}
		else if (char_n[0]=='-') {
			while (1) {
				printf ("\nPlease enter what parking you want (from 1 to %d): ", number_of_parking);
				fgets (char_n, n_max_number, stdin);
				number_of_parking2=strtol (char_n, NULL, 10);
				if (number_of_parking2<=0 || number_of_parking2>number_of_parking)
					printf ("\nError:\nBad number, please try again...");
				else break;
			}
			del_car (number_of_parking2, city_parking_pointer);
		}
		else if (char_n[0]=='a') {
			add_city_parking (city_parking_pointer, number_of_parking);
			number_of_parking++;
			if (number_of_parking==0) {
				printf ("\nFatality error:\nProgram will close...");
				return 0;
			}
		}
		else if (char_n[0]=='q')
			break;
		else printf ("\nError:\nBad command, please try again...");
	}
	free_all (city_parking_pointer, number_of_parking);
}
