#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void) {
  FILE *pf = fopen("ya.txt", "rt");
  char Buf[100];
  char cBuf[100];

  if (pf == NULL) {
    printf("Error opening file!\n");
    return 1;
  }

  FILE *file = fopen("textfile.txt", "wt");
  if (file == NULL) {
    printf("Error opening file!\n");
    return 1;
  }

  while (fgets(Buf, 100, pf) != NULL) {
    int j = 0;
    int flag_error = 0;

    for (int i = 0; i < strlen(Buf); i++) {
      if (isupper(Buf[i + 1])) {
        cBuf[j] = Buf[i];
        j++;
        cBuf[j] = '_';
        i++;
        j++;
      }
      if (Buf[i] != '_') {
        cBuf[j] = Buf[i];
        j++;
      }
      if (Buf[i] == '_' && isalpha(Buf[i - 1])) {
        cBuf[j] = ',';
        j++;
      }
      if ((Buf[i] == '_' && Buf[i + 1] == '_') ||
          (Buf[i] == '_' && Buf[i - 1] == '_') ||
          (isupper(Buf[i]) && isupper(Buf[i + 1])) ||
          (isupper(Buf[i]) && isupper(Buf[i - 1]))) {
        flag_error = 1;
        break;
      }
    }

    cBuf[j] = '\0';
    int counter = 0;
    if (flag_error == 0) {
      for (int a = 0; a < strlen(cBuf); a++) {
        if (ispunct(cBuf[a])) {
          cBuf[a + 1] = toupper(cBuf[a + 1]);
        }
        if (isdigit(cBuf[a])) {
          cBuf[a + 1] = toupper(cBuf[a + 1]);
        }
        if ((cBuf[a - 1] == '_') && isupper(cBuf[a])) {
          cBuf[a] = tolower(cBuf[a]);
        }
        if (cBuf[a] != ',') {
          cBuf[counter] = cBuf[a];
          counter++;
        }
      }
      cBuf[counter] = '\0';
      fputs(cBuf, file);
    } else {
      fputs("ERROR\n", file);
    }
  }

  fclose(file);
  fclose(pf);
  return 0;
}