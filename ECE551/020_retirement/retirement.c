#include <stdio.h>
#include <stdlib.h>
struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

void retirement(int startAge,         //in months
                double initial,       //initial savings in dollars
                retire_info working,  //info about working
                retire_info retired)  //info about being retired
{
  int year = startAge / 12;
  int month = startAge % 12;
  double amount = initial;  // in this work, amount -> the money;

  //Now I am calculating the working amount
  for (int i = 0; i < working.months; i++) {
    printf("Age %3d month %2d you have $%.2lf\n", year, month, amount);
    amount = (1 + working.rate_of_return) * amount + working.contribution;
    month += 1;
    if (month == 12) {
      year += 1;
      month = 0;
    }
  }

  // Now I am calculating the retirement amount
  for (int i = 0; i < retired.months; i++) {
    printf("Age %3d month %2d you have $%.2lf\n", year, month, amount);
    amount = (1 + retired.rate_of_return) * amount + retired.contribution;
    month += 1;
    if (month == 12) {
      year += 1;
      month = 0;
    }
  }
}

int main(void) {
  retire_info working = {489, 1000, 0.045 / 12};
  retire_info retired = {384, -4000, 0.01 / 12};

  retirement(327, 21345, working, retired);

  // getchar();
  return 1;
}
