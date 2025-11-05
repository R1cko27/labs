#include <stdio.h>
#include <stdlib.h>
int max_num(int arr[], int size){
    int max_num = arr[0];
    for (int i = 0; i < size; i++){
        if (arr[i] > max_num){
            max_num = arr[i];
        }
    }
    return max_num;
}
int min_num(int arr[], int size){
    int min_num = arr[0];
    for (int i = 0; i < size; i++){
        if (arr[i] < min_num){
            min_num = arr[i];
        }
    }
    return min_num;
}

void find(int arr[], int size){
    int max_number = max_num(arr, size);
    int min_number = min_num(arr, size);
    printf("%d\t%d\n",max_number,min_number);
    int summ = 0;
    for (int i = 0; i < size; i++){
        if (arr[i] == max_number){
            printf("\nFirst is max\n");
            for (int j = i; j < size; j++){
                if (arr[j] != min_number){
                    summ += arr[j];
                    printf("+ %d\t", arr[j]);
                } else{
                    summ += arr[j];
                    printf("+ %d\t", arr[j]);
                    break;
                }
            }
        break;
        } else if (arr[i] == min_number){
            printf("\nFirst is min\n");
            for (int j = i; j < size; j++){
                if (arr[j] != max_number){
                    summ += arr[j];
                    printf("+ %d\t", arr[j]);
                } else{
                    summ += arr[j];
                    printf("+ %d\t", arr[j]);
                    break;
                }
            }
        break;
        }
    }
    printf("\nAnswer - %d", summ);
}

int main(){
    int size = 0;
    printf("%s", "Enter size: ");
    scanf("%d", &size);
    int *arr = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++){
        int temp;
        printf("Enter the %d element: ", i);
        scanf("%d", &temp);
        arr[i] = temp;
    }
    find(arr, size);
    free(arr);
    return 0;
}