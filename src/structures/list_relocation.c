#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list_relocation.h"
#include "../../include/notify.h"

void print_list_relocation(Relocation_t * head) {
  // Print all elements on list
  Relocation_t * current = head->next;

  printf("\nLIST DE RELOCATION ==>>\n");

  while (current != NULL) {
    printf("address: 0x%02X | %s | .%s:0x%02X | %s\n", current->address_instru, current->type_relocation, current->section, current->address_etiquette, current->symbole);
    current = current->next;
  }

  printf("\n");
}

void push_Relocation(Relocation_t * head, int address_instru, int address_etiquette, char * section, char * type_relocation, char * symbole) {
  // ADD element on top of the linked list
  Relocation_t * current = head;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = malloc(sizeof(Relocation_t));
  current->next->address_instru = address_instru;
  current->next->address_etiquette = address_etiquette;
  current->next->section = section;
  current->next->type_relocation = type_relocation;
  current->next->symbole = symbole;
  current->next->next = NULL;
}

bool is_empty_Relocation(Relocation_t * head) {
  // Verify if the list is EMPTY
  if (head->next == NULL) return true;
  return false;
}

Relocation_t * new_Relocation() {
  // Create a new struvture of type Relocation_t
  // and inicializes the head with HEAD -1
  Relocation_t * head = NULL;
  head = malloc(sizeof(Relocation_t));
  head->address_instru = -1;
  head->address_etiquette = -1;
  head->section = NULL;
  head->type_relocation = NULL;
  head->symbole = NULL;
  return head;
}
