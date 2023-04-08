#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Contact{
	char name[100];
	char number[9];
	char email[100];
}Contact;

typedef struct Node{
	Contact c;
	struct Node *next;
}Node; 

typedef struct ContactBook{
	Node *head;
	Node *tail;
	int size;
}ContactBook;

ContactBook createContactBook(){
	ContactBook b;
	b.head = b.tail = NULL;
	b.size = 0;
	return b;
}

int isEmpty(ContactBook cb){
	return(cb.head == NULL && cb.tail == NULL && cb.size == 0);
}

Contact createContact(){
	Contact c;
	printf("Enter Contact Name: ");
	scanf("%s",c.name);
	printf("Enter Contact Number: ");
	scanf("%s",c.number);
	printf("Enter Contact Email: ");
	scanf("%s",c.email);
	return c;
}

void addContact(ContactBook *cb,Contact c){
	Node *n;
	n = (Node *)malloc(sizeof(Node));
	n->c = c;
	n->next = NULL;
	
	if(isEmpty(*cb)){
		cb->head = n;
	}
	else{
		cb->tail->next = n;
	}
	cb->tail = n;
	(cb->size)++;
}

void displayContact(Contact c){
	printf("Contact name is %s\n",c.name);
	printf("Contact number is %s\n",c.number);
	printf("Contact email is %s\n",c.email);
}

void displayContactBook(ContactBook cb){
	if(isEmpty(cb)){
		printf("Contact Book is Empty!!\n\n");
	}
	else{
		Node *it = cb.head;
		for(int i = 1;i <= cb.size;i++){
			printf("Contact %d :\n\n",i);
			displayContact(it->c);
			printf("----------------------------\n");
			it = it->next;
		}
	}
	
}

void removeContact(ContactBook *cb,char *name){
	if(strcmp(cb->head->c.name,name) == 0 ){
		Node *temp = cb->head;
		cb->head = temp->next;
		free(temp);
		(cb->size)--;
	}
	else{
		Node *before = cb->head,*after;
		while(before != NULL){
			if(strcmp(before->next->c.name,name) == 0){
				break;
			}
			before = before->next;
		}
		if(before != NULL){
			after = before->next;
			before->next = after->next;
			free(after);
			(cb->size)--;
		}
		else{
			printf("Contact Not Found!!");
		}
	}
	
}

int searchByName(ContactBook cb,char *name){
	Node *it = cb.head;
	while(it != NULL){
		if(strcmp(it->c.name,name) == 0){
			displayContact(it->c);
			return 1;
		}
		it = it->next;
	}
	printf("Contact Not Found!!");
	return 0;
}

int searchByNumber(ContactBook cb,char *number){
	Node *it = cb.head;
	while(it != NULL){
		if(strcmp(it->c.number,number) == 0){
			displayContact(it->c);
			return 1;
		}
		it = it->next;
	}
	printf("Contact Not Found!!");
	return 0;
}

int updateAll(ContactBook *cb,char *name,char *newname,char *newnumber,char *newemail){
	Node *it = cb->head;
	while(it != NULL){
		if(strcmp(it->c.name,name) == 0){
			strcpy(it->c.name,newname);
			strcpy(it->c.number,newnumber);
			strcpy(it->c.email,newemail);
			return 1;
		}
		it = it->next;
	}
		printf("Contact Not Found!!");
		return 0;
}

int updateName(ContactBook *cb,char *name,char *newname){
	Node *it = cb->head;
	while(it != NULL){
		if(strcmp(it->c.name,name) == 0){
			strcpy(it->c.name,newname);
			
			return 1;
		}
		it = it->next;
	}
		printf("Contact Not Found!!");
		return 0;
}

int updateNumber(ContactBook *cb,char *name,char *newnumber){
	Node *it = cb->head;
	while(it != NULL){
		if(strcmp(it->c.name,name) == 0){
			strcpy(it->c.number,newnumber);
			return 1;
		}
		it = it->next;
	}
		printf("Contact Not Found!!");
		return 0;
}

int updateEmail(ContactBook *cb,char *name,char *newemail){
	Node *it = cb->head;
	while(it != NULL){
		if(strcmp(it->c.name,name) == 0){
			strcpy(it->c.email,newemail);
			return 1;
		}
		it = it->next;
	}
		printf("Contact Not Found!!");
		return 0;
}

void displayContact2(Contact c,FILE *fp){
	fprintf(fp,"Contact name is %s\n",c.name);
	fprintf(fp,"Contact number is %s\n",c.number);
	fprintf(fp,"Contact email is %s\n",c.email);
}

void writeIntoFile(ContactBook cb,FILE *fp){
	
	Node *it = cb.head;
	for(int i = 1;i <= cb.size;i++){
		fprintf(fp,"----------------------------\n");
		fprintf(fp,"Contact %d :\n\n",i);
		displayContact2(it->c,fp);
		it = it->next;
	}
	
}

void fillString(FILE *fp, char *name){
	char c;
	for(int i = 0;i<100;i++){
		c = fgetc(fp);
		if(c == '\n'){
		break;
		}
		else{
			name[i] = c;
		}
	}
}

int readFromFile(ContactBook *cb,FILE *fp){
	char s[255],name[100],number[9],email[100],c;
	int n = 255;
	for(int i = 0;i<3;i++){
		fgets(s,n,fp);	
	}
	
	fseek(fp,16,SEEK_CUR);
	fillString(fp,name);
	
	fseek(fp,18,SEEK_CUR);
	fillString(fp,number);
	
	fseek(fp,17,SEEK_CUR);
	fillString(fp,email);
	
	Contact cn = {"","",""};
	strcpy(cn.name,name);
	strcpy(cn.number,number);
	strcpy(cn.email,email);
	
	addContact(cb,cn);
	
	if(fgetc(fp) != '-'){
		return 1;
	}
	readFromFile(cb,fp);
}

void menu(ContactBook *cb){
	FILE *fp;
	if(((fp = fopen("ContactBookFile.txt","r")) != NULL) && isEmpty(*cb)){
		
		readFromFile(cb,fp);
		fclose(fp);
	}
	char choice[50];
	printf("Choose: \n\n");
	printf("1- displayContactBook\n");
	printf("2- addContact\n");
	printf("3- deleteContact\n");
	printf("4- updateContact\n");
	printf("5- searchByName\n");
	printf("6- searchByNumber\n");
	printf("7- exit\n");
	printf("---------------------------------\n\n");
	printf(">");
	scanf("%s",choice);
	printf("\n");
	
	if(strcmp(choice,"displayContactBook") == 0){
		displayContactBook(*cb);
	}
	else if(strcmp(choice,"addContact") == 0){
		Contact c = createContact();
		addContact(cb,c);
		fp = fopen("ContactBookFile.txt","w");
		writeIntoFile(*cb,fp);
		fclose(fp);
	}
	else if(strcmp(choice,"deleteContact") == 0){
		char name[100];
		printf("Enter Contact Name: ");
		scanf("%s",name);
		removeContact(cb,name);
		fp = fopen("ContactBookFile.txt","w");
		writeIntoFile(*cb,fp);
		fclose(fp);
	}
	else if(strcmp(choice,"updateContact") == 0){
		char name[100],newName[100],newNumber[100],newEmail[100];
		printf("Enter Contact Name: ");
		scanf("%s",name);
		printf("Enter NewName: ");
		scanf("%s",newName);
		printf("Enter NewNumber: ");
		scanf("%s",newNumber);
		printf("Enter NewEmail: ");
		scanf("%s",newEmail);
		updateAll(cb,name,newName,newNumber,newEmail);
		fp = fopen("ContactBookFile.txt","w");
		writeIntoFile(*cb,fp);
		fclose(fp);
	}
	else if(strcmp(choice,"searchByName") == 0){
		char name[100];
		printf("Enter Contact Name: ");
		scanf("%s",name);
		searchByName(*cb,name);
	}
	else if(strcmp(choice,"searchByNumber") == 0){
		char number[100];
		printf("Enter Contact Number: ");
		scanf("%s",number);
		searchByName(*cb,number);
	}
	else if(strcmp(choice,"exit") == 0){
		exit(0);
	}
	else{
		printf("Input not Valid!!!");
	}
	printf("\n");
	menu(cb);
}



int main(){
	ContactBook cb = createContactBook();
	menu(&cb);
	return 0;
}