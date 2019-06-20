#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char name[][10] = {"빵", "상추", "피클", "새우", "토마토", "닭고기", "치즈"};

typedef struct _process{
	char * _pnum;
	char * arrt;
	char * method;
	char * menu;
}process;

int loc = 0;

float SSTF(int remaincount[], int tablesize, int menu){
	int MAXSIZE = 50;
	int retun = 10, i, temp = 0;
	loc = menu;
	remaincount[loc] = retun;
	for(i = 0;i < tablesize;i++){
		temp += remaincount[i];
	}
	if(temp > 50){
		remaincount[loc] = remaincount[loc] - (temp - 50);
	}
//	printf("%s을(를) %d개 창고B에서 가져왔습니다.\n", name[menu], remaincount[loc]);
	return remaincount[loc] * 0.1;
}

float PAGE(int menu, int table[], int tablesize, int remaincount[]){
    int check, temp, flag, i, j, count = 0, temp2, k;
	int arr[7];
	int temparr[7];
	float ta = 0;
	for(i = 0;i < 7;i++){
		arr[i] = -1;
		temparr[i] = -1;
	}
    for(check = 0; check < tablesize; check++){
		if(remaincount[check] == 0){
            arr[count++] = check;
        }
    }

	if(count != 0){
		flag = 2;
	}else{
		flag = 1;
	}

    switch(flag){
        case 1:
			if(menu == 110){
				arr[0] = 0;
				arr[1] = 1;
				arr[2] = 2;
				arr[3] = 3;
				arr[4] = 4;
			}else{
				arr[0] = 0;
				arr[1] = 1;
				arr[2] = 2;
				arr[3] = 5;
				arr[4] = 6;
			}
            for(temp = 0;arr[temp] != -1;temp++){
				for(i = arr[temp];i < tablesize - 1;i++){
                	table[i] = table[i + 1];
            	}
            	table[tablesize - 1] = arr[temp];
				remaincount[arr[temp]]--;
				ta += 1;
			}
/*			for(i = tablesize - 1; i >= 0;i--){
                printf("%d\n",remaincount[i]);
            }
			printf("\n%d\n\n", menu); */
			ta++;
            break;
        case 2:
			for(i = 0;arr[i] != -1;i++){
				temparr[i] = abs(arr[i] - loc);
				k = i;
			}
			for(i = k; i > 0;i--){
				for(j = 0;j < i;j++){
					if(temparr[j] > temparr[j+1]){
						temp2 = arr[j+1];
						arr[j+1] = arr[j];
						arr[j] = temp2;
					}
				}
			}
//			printf("%d\n\n", loc);
            for(temp = 0;arr[temp] != -1;temp++){
				remaincount[table[0]] = 0;
				for(i = arr[temp];i < tablesize - 1;i++){
                	table[i] = table[i + 1];
            	}
            	table[tablesize - 1] = arr[temp];
				ta += SSTF(remaincount, tablesize, arr[temp]);
//				printf("%.2f\n", ta);
				remaincount[arr[temp]]--;
				ta += 1;
//				printf("%d\n", arr[temp]);
			}
//			printf("\n");
/*			for(i = tablesize - 1; i >= 0;i--){
                printf("%d\n",remaincount[i]);
            }
			printf("\n%d\n\n", menu); */
            break;
	}
	return ta;
}

void sortp(process * pro, int index){
	process temp;
	int i,j;
	for(i = index - 1; i > 0;i--){
		for(j = 1;j < i;j++){
			if(strcmp(pro[j].arrt, pro[j+1].arrt) > 0){
				temp = pro[j+1];
				pro[j+1] = pro[j];
				pro[j] = temp;
			}
		}
	}
}

void RR(int queue[], process * pro, int index, int Q, int remainintarr[][10], int remainint[], float bursttime[], float arrtarr[], float turnaround[], float waittime[], int * table, int tablesize, char * remainarr[][1024], int * order, int * ord_aft, int * deliv, int remaincount[]){
	int i, j, pnum = 1, pnum2 = 1, pnum3 = 1, count = 0, count2 = 0, count3 = 0, wait, temp, temp2, pcheck = index - 1, act = 0, rider = 0;
	int check[index];
	int que[index];
	float ta = 0;
	float * tap = &ta;

	for(i = 1; i < index; i++){
		check[i] = 0;
		que[i] = 0;
 	}

	while(count != index - 1){
		if(remainintarr[pnum][que[pnum]] == 0 || remainint[pnum] == 0){
			if(remainint[pnum] == 0 && deliv[pnum] <= 0){
				if(pnum < index - 1){
					pnum++;
				}
				else{
					pnum = 1;
				}
				continue;
			}
			if(remainint[pnum] != 0 && remainintarr[pnum][que[pnum]] == 0){
				if(que[pnum] > queue[pnum]){
					if(pnum < index - 1){
						pnum++;
					}
					else{
						pnum = 1;
					}
					continue;
				}
				que[pnum]++;
				if(pnum < index - 1){
					pnum++;
				}
				else{
					pnum = 1;
				}
				continue;
			}
		}
		if(arrtarr[pnum] > ta){
			if(act != 0){
				if(pnum < index - 1){
					pnum++;
				}
				else{
					pnum = 1;
				}
			}
			else{
				ta++;
			}
			continue;
		}
		temp = Q;

		if(order[pnum] > 0){
			for(i = 1; i <= Q; i++){
				if(order[pnum] == 0){
					temp = i;
					break;
				}
				else{
					order[pnum]--;
					if(order[pnum] == 0){
						temp = i;
						break;
					}
				}
			}
			ta += temp;
			turnaround[pnum] = ta;
			temp = Q;
			if(ord_aft[pnum] > 0 && order[pnum] == 0){
				for(i = 1; i <= Q; i++){
					if(ord_aft[pnum] == 0){
						temp = i;
						break;
					}
					else{
						ord_aft[pnum]--;
						if(ord_aft[pnum] == 0){
							temp = i;
							break;
						}
					}
				}
				ta += temp;
				turnaround[pnum] = ta;
				temp = Q;
			}
		}
		if(order[pnum] == 0 && ord_aft[pnum] == 0 && remainint[pnum] > 0){
		for(i = 1; i <= Q; i++){
			if(remainint[pnum] == 0){
				temp = i;
				break;
			}
			else if(remainintarr[pnum][que[pnum]] == 0){
				temp = i;
				break;
			}
			else{
				if(!strcmp(remainarr[pnum][que[pnum]], "새우") && remainintarr[pnum][que[pnum]] == 110){
					temp2 = PAGE(remainintarr[pnum][que[pnum]], table, tablesize, remaincount);
					ta += temp2;
				}else if(!strcmp(remainarr[pnum][que[pnum]], "닭고기") && remainintarr[pnum][que[pnum]] == 100){
					temp2 = PAGE(remainintarr[pnum][que[pnum]], table, tablesize, remaincount);
					ta += temp2;
				}
				remainintarr[pnum][que[pnum]]--;
				remainint[pnum]--;
//				printf("%d %d\n", remainintarr[pnum][que[pnum]], remainint[pnum]);
				if(remainint[pnum] == 0){
					temp = i;
					break;
				}else if(remainintarr[pnum][que[pnum]] == 0){
					temp = i;
					break;
				}
			}
		}
		ta = ta + temp;
		turnaround[pnum] = ta;
		temp = Q;
		}

		if(remainint[pnum] == 0 && !strcmp(pro[pnum].method, "전화") && deliv[pnum] > 0){
			for(i = 1; i <= Q; i++){
				if(deliv[pnum] == 0){
					temp = i;
					count++;
					act--;
					break;
				}
				else{
					deliv[pnum]--;
					if(deliv[pnum] == 0){
						temp = i;
						count++;
						act--;
						break;
					}
				}
			}
			ta += temp;
			turnaround[pnum] = ta;
		}
		else if(remainint[pnum] == 0 && !strcmp(pro[pnum].method, "방문")){
//			printf("P%s : %d \ncount : %d\nindex : %d\nta : %d\nact : %d\nQ : %d\ndeliv : %d\norder : %d\nafter : %d\n\n", pro[pnum]._pnum, remainint[pnum], count, index, turnaround[pnum], act, Q, deliv[pnum], order[pnum], ord_aft[pnum]);
			count++;
			act--;
		}
		if(turnaround[pnum] != 0 && check[pnum] == 0){
			act++;
			check[pnum] = 1;
		}
//		printf("P%s : %d \ncount : %d\nindex : %d\nta : %d\nact : %d\nQ : %d\ndeliv : %d\norder : %d\nafter : %d\n\n", pro[pnum]._pnum, remainint[pnum], count, index, turnaround[pnum], act, Q, deliv[pnum], order[pnum], ord_aft[pnum]);
		if(pnum < index - 1){
			pnum++;
		}
		else{
			pnum = 1;
		}
	}
	for(i = 1; i < index; i++){
		turnaround[i] -= arrtarr[i];
		waittime[i] = turnaround[i] - bursttime[i];
//		printf("%d %d %d %s\n", waittime[i], turnaround[i], arrtarr[i], pro[i].method);
 	}
}

int main(int argc, char * argv[]){
	int n = 0, i = 0, j = 0, Q, num1, num2, det, cnt = 0, tablesize = 7;
	int table[tablesize];
	int remaincount[tablesize];
	FILE * list;
	FILE * result;
	char * lines[50];
	char * line = NULL;
	char * temp;
	char * temp2;
	size_t len = 0;
	ssize_t read;

	for(i = 0;i < tablesize;i++){
		table[i] = i;
		remaincount[i] = 7;
	}

	process * pro = (process *)malloc(sizeof(process));

	list = fopen(argv[1], "r");
	result = fopen("result.txt", "w");
	if(list == NULL){
		printf("file read error!!");
		exit(1);
	}
	else{
		while((read = getline(&line, &len, list)) != -1) { 
			char* newstrptr = (char*)malloc(sizeof(char) * (len));
			strcpy(newstrptr, line);
			lines[n] =  newstrptr;
			n++;
    	}
		float arrtarr[n];
		char * remainarr[n][1024];
		int queue[n];
		int remainint[n];
		int remainintarr[n][10];
		float bursttime[n];
		float turnaround[n];
		float waittime[n];
		int order[n];
		int ord_aft[n];
		int deliv[n];		
		for(i = 1;i < n; i++){
			temp = strtok(lines[i], "\t");
			pro[i]._pnum = (char *)malloc(sizeof(temp)+1024);
			strcpy(pro[i]._pnum, temp);
//			printf("%s ", pro[i]._pnum);
			temp = strtok(NULL, "\t");
			pro[i].arrt = (char *)malloc(sizeof(temp)+1024);
			strcpy(pro[i].arrt, temp);
//			printf("%s ", pro[i].arrt);
			temp = strtok(NULL, "\t");
			pro[i].method = (char *)malloc(sizeof(temp)+1024);
			strcpy(pro[i].method, temp);
//			printf("%s ", pro[i].method);
			temp = strtok(NULL, "\t");
			pro[i].menu = (char *)malloc(sizeof(temp)+1024);
			strcpy(pro[i].menu, temp);
//			printf("%s", pro[i].menu);
		}

		free(line);
		fclose(list);
		
		sortp(pro, n);
		sscanf(lines[0], "Q=%d", &Q);
//		printf("%d", Q);
		for(i = 1;i < n; i++){
			temp2 = (char *)malloc(sizeof(pro[i].menu));
			strcpy(temp2, pro[i].menu);
			temp = (char *)malloc(sizeof(temp2));
			temp = strtok(temp2, ",\n");
			remainarr[i][cnt] = (char *)malloc(sizeof(temp) + 1024);
			strcpy(remainarr[i][cnt], temp);
//			printf("%s\n", remainarr[i][cnt]);
			cnt++;
			while(temp != NULL){
				temp = strtok(NULL, ",\n");
				if(temp == NULL){
					break;
				}
	//			printf("%s", temp);
				remainarr[i][cnt] = (char *)malloc(sizeof(temp) + 1024);
				strcpy(remainarr[i][cnt], temp);
	//			printf("%s", remainarr[i][cnt]);
				cnt++;
			}
//			printf("%d", cnt);
//			printf("\n");
			queue[i] = cnt;
			cnt = 0;
		}
		for(i = 1;i < n; i++){
			sscanf(pro[i].arrt, "%2d:%2d", &num1, &num2);
			arrtarr[i] = 3600*num1 + 60*num2;
//			printf("%d\n", arrtarr[i]);			
    	}
		for(i = 1;i < n; i++){
//			printf("%s %s %s %s", pro[i]._pnum, pro[i].arrt, pro[i].method, pro[i].menu);
			remainint[i] = 0;
			bursttime[i] = 0;
			turnaround[i] = 0;
			waittime[i] = 0;
			ord_aft[i] = 5;
			if(!strcmp(pro[i].method, "전화")){
				deliv[i] = 200;
				order[i] = 3;
			}else{
				deliv[i] = -1;
				order[i] = 5;
			}
    	}
		for(i = 1;i < n; i++){
			for(j = 0;j < queue[i];j++){
				if(!strcmp(remainarr[i][j], "새우")){
					remainintarr[i][j] = 110;
					remainint[i] += 110;
					bursttime[i] += 110;
				}else if(!strcmp(remainarr[i][j], "닭고기")){
					remainintarr[i][j] = 100;
					remainint[i] += 100;
					bursttime[i] += 100;
				}
//				printf("%d %d %s %d %d\n", i, j, remainarr[i][j], remainint[i], remainintarr[i][j]);
			}
		}
		RR(queue, pro, n, Q, remainintarr, remainint, bursttime, arrtarr, turnaround, waittime, table, tablesize, remainarr, order, ord_aft, deliv, remaincount);
//		fprintf(result, "Q=%d\n", Q);
		for(i = 1;i < n;i++){
			fprintf(result, "%s\t%s\t%s\t%.1f\t%.1f\n", pro[i]._pnum, pro[i].arrt, pro[i].method, bursttime[i], turnaround[i]);
		}
		fprintf(result, "\n냉장고 상태\n");
		fprintf(result, "빵 : %d\n상추 : %d\n피클 : %d\n새우 : %d\n토마토 : %d\n닭고기 : %d\n치즈 : %d\n\n", remaincount[0], remaincount[1], remaincount[2], remaincount[3], remaincount[4], remaincount[5], remaincount[6]);
		for(i = 1;i < n;i++){
			for(j = 0;j < queue[i];j++){
				free(remainarr[i][j]);
			}
		}
	}
	for(i = 1;i < n; i++){
		free(pro[i]._pnum);
		free(pro[i].arrt);
		free(pro[i].method);
		free(pro[i].menu);
		free(lines[i]);
	}
	fclose(result);
	return 0;
}