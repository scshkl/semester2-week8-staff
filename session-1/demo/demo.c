#include <stdio.h>
#include "pet.h"
#include <string.h>
#include <stdlib.h>

int main(void){

    // function prototype
    void print_details(Pet p);
    void update_weight(Pet *p, float weight);

    // Part 1: struct
    // struct pet my_pet;
    // strcpy(my_pet.name, "Timmy");
    // strcpy(my_pet.species, "Dog");
    // strcpy(my_pet.breed, "Jack Russle Terrier");
    // my_pet.age = 18;
    // strcpy(my_pet.sex , "Male");
    // my_pet.weight = 4.8;

    // printf("=============My Pet =============\n");
    // printf("Name: %s, species: %s, breed: %s\n", my_pet.name, my_pet.species, my_pet.breed);
    // printf("Age: %d, sex: %s, weight: %.2f\n\n", my_pet.age, my_pet.sex, my_pet.weight);

    // my_pet.weight = 5.4;
    // printf("updated weight: %.2f\n\n",  my_pet.weight);

    // struct pet mpet= {
    //     .name = "Beau",
    //     .species = "Cat",
    //     .breed = "Domestic Longhair",
    //     .age = 2,
    //     .sex = "Female",
    //     .weight = 2.2
    // };
    // printf("Name: %s, species: %s, breed: %s\n", mpet.name, mpet.species, mpet.breed);
    // printf("Age: %d, sex: %s, weight: %.2f\n\n", mpet.age, mpet.sex, mpet.weight);


    // Part 2: typedef struct
    Pet my_pet2 = {
        .name = "Timmy",
        .species = "Dog",
        .breed = "Jack Russle Terrier",
        .age = 17,
        .sex = "Male",
        .weight = 5.2
    };

    // printf("=============My Pet2 =============\n");
    // printf("Name: %s, species: %s, breed: %s\n", my_pet2.name, my_pet2.species, my_pet2.breed);
    // printf("Age: %d, sex: %s, weight: %.2f\n\n", my_pet2.age, my_pet2.sex, my_pet2.weight);

    // Part 3: pointer to structure
    // Pet *pet_pointer;
    // pet_pointer = &my_pet2;
    // pet_pointer->weight = 4.9;

    // not going to work // pet_pointer.weight = 4.9;
    // printf("Updated weight: %.2f\n\n", my_pet2.weight);

    // Part 4: dynamically allocate structure data
    // Pet *pPets = calloc(2, sizeof(Pet));

    // strcpy(pPets[0].name, "Louis");
    // printf("Name: %s\n\n", pPets[0].name);
    // free(pPets);

    // Part 5: passing structure as an argument
    print_details(my_pet2);
    update_weight(&my_pet2, 3.5);
    print_details(my_pet2);

    return 0;
}

// function implementation

void print_details(Pet p){
    printf("=============My Pet =============\n");
    printf("Name: %s, species: %s, breed: %s\n", p.name, p.species, p.breed);
    printf("Age: %d, sex: %s, weight: %.2f\n\n", p.age, p.sex, p.weight);
}

void update_weight(Pet *p, float weight){
    if (p!= NULL && weight > 0){
        p->weight = weight;
    }
}