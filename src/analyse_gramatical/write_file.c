#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../structures/list_lexeme.h"
#include "../structures/list_etiquette.h"
#include "../structures/list_relocation.h"
#include "etiquette.h"
#include "division_section.h"
#include "analyse_bss.h"
#include "analyse_data.h"
#include "analyse_text.h"
#include "analyse_gramatical_1.h"
#include "analyse_symboles.h"
#include "analyse_type_instruction.h"
#include "analyse_relocation.h"
#include "create_code_binaire.h"


bool write_file_Coll_INSTRU_with_code(Coll_INSTRU_t * head, FILE * file, int line) {
  /* Print all elements on list */
  if (head->next == NULL) {
    return false;
  }
  Coll_INSTRU_t * current = head->next;
  bool wrote = false;

  while (current != NULL) {
    if (current->ligne == line) {
      if (current->n_op == 0) {
        fprintf(file, "%3u %08X %08X %s\n", current->ligne, current->decalage, current->code_binaire_instru, current->instruction);
        wrote = true;
      }
      else if (current->n_op == 1) {
        fprintf(file, "%3u %08X %08X %s %s\n", current->ligne, current->decalage, current->code_binaire_instru, current->instruction, current->op1);
        wrote = true;
      }
      else if (current->n_op == 2) {
        fprintf(file, "%3u %08X %08X %s %s, %s\n", current->ligne, current->decalage, current->code_binaire_instru, current->instruction, current->op1, current-> op2);
        wrote = true;
      }
      else {
        fprintf(file, "%3u %08X %08X %s %s, %s, %s\n", current->ligne, current->decalage, current->code_binaire_instru, current->instruction, current->op1, current-> op2, current->op3);
        wrote = true;
      }
    }
    current = current->next;
  }
  return wrote;
 }

bool write_file_Coll_DATA_with_code(Coll_DATA_t * head, FILE * file, int line) {
  /* Print all elements on list */
  if (head->next == NULL) {
    return false;
  }
  bool wrote = false;
  Coll_DATA_t * current = head->next;

  while (current != NULL) {
    if (current->ligne == line) {
      fprintf(file, "%3u %08X %08X %s %s\n", current->ligne, current->decalage, current->code_binaire, current->directive, current->valeur);
      wrote = true;
    }
    current = current->next;
  }
  return wrote;
}

bool write_file_COLL_BSS_with_code(Coll_BSS_t * head, FILE * file, int line) {
  /* Print all elements on list */
  if (head->next == NULL) {
    return false;
  }

  Coll_BSS_t * current = head->next;
  bool wrote = false;

  while (current != NULL) {
    if (current->ligne == line) {
      fprintf(file, "%3u %08X %08X %s %s\n", current->ligne, current->decalage, current->code_binaire, current->directive, current->valeur);
      wrote = true;
    }
    current = current->next;
  }
  return wrote;
}

int find_number_lines(Coll_INSTRU_t * head_coll_instru, Coll_DATA_t * head_coll_data, Coll_BSS_t * head_coll_bss) {
  int max_lines = 0;

  if (get_max_lines_bss(head_coll_bss) > max_lines) max_lines = get_max_lines_bss(head_coll_bss);
  if (get_max_lines_data(head_coll_data) > max_lines) max_lines = get_max_lines_data(head_coll_data);
  if (get_max_lines_instru(head_coll_instru) > max_lines) max_lines = get_max_lines_instru(head_coll_instru);

  return max_lines;
}

void write_file_list_etiquette(Etiquette_t * head, FILE * file) {
  /* Print all elements on list */
  Etiquette_t * current = head->next;

  fprintf(file, "\n.symtab\n");

  while (current != NULL) {
    fprintf(file, "%3d\t.%-4s:%08X\t%s\n", current->ligne, current->section, current->decalage, current->word);
    current = current->next;
  }
}

void write_file_list_relocation(Relocation_t * head, FILE * file) {
  /* Print all elements on list */
  Relocation_t * current = head->next;

  while (current != NULL) {
    fprintf(file, "%08x\t%s\t.%-4s:%08x\t%s\n", current->address_instru, current->type_relocation, current->section, current->address_etiquette, current->symbole);
    current = current->next;
  }
}

void write_file(Coll_INSTRU_t * head_coll_instru, Coll_DATA_t * head_coll_data, Coll_BSS_t * head_coll_bss, Etiquette_t * head_etiquettes, Relocation_t * head_relocation_text, Relocation_t * head_relocation_data, FILE * file) {
  int i = 1;
  int max_lines = find_number_lines(head_coll_instru, head_coll_data, head_coll_bss);
  for (i = 1; i <= max_lines; i++) {
    if (write_file_Coll_INSTRU_with_code(head_coll_instru, file, i) \
    || write_file_Coll_DATA_with_code(head_coll_data, file, i) \
    || write_file_COLL_BSS_with_code(head_coll_bss, file , i)

    ) {

    }

    else {
      fprintf(file, "%3u\n", i);
    }
  }

  write_file_list_etiquette(head_etiquettes, file);
  fprintf(file, "\nrel.text\n");
  write_file_list_relocation(head_relocation_text, file);
  fprintf(file, "\nrel.data\n");
  write_file_list_relocation(head_relocation_data, file);

}

void write_file_obj(Coll_INSTRU_t * head_coll_instru, Coll_DATA_t * head_coll_data, Coll_BSS_t * head_coll_bss, FILE * file) {
  fprintf(file, "%s\n", "000000008877665544");

  Coll_INSTRU_t * current = head_coll_instru;
  while (next_instru(current) != NULL) {
    current = next_instru(current);
    fprintf(file, "%d\n", get_code_binaire_final(current));
  }
}
