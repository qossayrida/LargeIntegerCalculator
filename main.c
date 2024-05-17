#include <stdio.h>
#include <stdlib.h>

// Rename node pointer for double linked list
typedef struct nodeContainDigit* Digit;
typedef Digit Integer;

// Rename node pointer for single linked list
typedef struct nodeContainInteger* Pos;
typedef Pos ListOfInteger;

// Node for double linked list
struct nodeContainDigit{
    int Data;
    Digit Next;
    Digit Prev;
};

// Node for single linked list
struct nodeContainInteger {
    Integer Data;
    Pos Next;
    int count ;
};

// Function to read from file and print menu
ListOfInteger readFile ();
int PrintMenu();

// Function for double linked list
Integer CreateInteger ();
void AddDigitAtBeginning (int Data , Integer L);
void AddDigitAtEnd (int Data , Integer L);
void PrintInteger(Integer L);
void fPrintInteger(Integer num,int ResOrReminder);
void PrintIntegerPrev(Integer L);
Integer length(Integer L);
Digit LastNode (Integer L);
Integer MakeCopy(Integer num);
int compare(Integer num1, Integer num2);
void reverse(Integer L);

// Function for single linked list
ListOfInteger CreateList ();
void AddInteger (Integer Data,ListOfInteger L);
Integer findInteger (int count , ListOfInteger List);

// Arithmetic operation
Integer Add(Integer num1 ,Integer num2);
Integer Sub(Integer num1, Integer num2);
Integer Mul(Integer num1, Integer num2);
Integer Div(Integer num1, Integer num2,Integer Rem);


int main(){
    printf("*********** Welcome to our calculator app ***********");
    ListOfInteger List = NULL;
    int operation = 0;
    Integer result , num1 ,num2 ;
    int index1 , index2;

    while (operation != 7){
        operation = PrintMenu();
        switch (operation) {
            case 1: // call function readFile() to read all integer from file
                    List = readFile();
                    break;
            case 2: if (List==NULL)
                        printf("Please read the numbers from the file first\n");
                    else{
                        // print all integer exit in list with index
                        printf("All number in file\n");
                        Pos integer = List->Next;
                        while (integer != NULL){
                            printf("%d- ",integer->count);
                            // print integer from last node because store reversely
                            PrintIntegerPrev(integer->Data);
                            integer = integer->Next;
                        }
                    }
                    break;
            case 3: printf("Please choose two number to add\n");
                    // read the index of number from user
                    scanf("%d%d",&index1,&index2);
                    // find Integers to do operation on it
                    num1 = findInteger(index1,List);
                    num2 = findInteger(index2,List);
                    if (num1 == NULL || num2 == NULL){
                        printf("chosen invalid number\n");
                        break;
                    }
                    // find result and print it
                    result = Add(num1,num2);
                    printf("result= ");
                    PrintInteger(result);
                    fPrintInteger(result,0);
                    break;
            case 4: printf("Please choose two number to subtract\n");
                    // read the index of number from user
                    scanf("%d%d",&index1,&index2);
                    // find Integers to do operation on it
                    num1 = findInteger(index1,List);
                    num2 = findInteger(index2,List);
                    if (num1 == NULL || num2 == NULL){
                        printf("chosen invalid number\n");
                        break;
                    }
                    // find result and print it
                    result = Sub(num1,num2);
                    printf("result= ");
                    PrintInteger(result);
                    fPrintInteger(result,0);
                    break;
            case 5: printf("Please choose two number to multiply\n");
                    // read the index of number from user
                    scanf("%d%d",&index1,&index2);
                    // find Integers to do operation on it
                    num1 = findInteger(index1,List);
                    num2 = findInteger(index2,List);
                    if (num1 == NULL || num2 == NULL){
                        printf("chosen invalid number\n");
                        break;
                    }
                    // find result and print it
                    result = Mul(num1,num2);
                    printf("result= ");
                    PrintInteger(result);
                    fPrintInteger(result,0);
                    break;
            case 6: printf("Please choose two number to divide\n");
                    // read the index of number from user
                    scanf("%d%d",&index1,&index2);
                    // find Integers to do operation on it
                    num1 = findInteger(index1,List);
                    num2 = findInteger(index2,List);
                    if (num1 == NULL || num2 == NULL){
                        printf("chosen invalid number\n");
                        break;
                    }
                    // find result and print it, if don't divide by zero
                    // create Integer to save reminder
                    Integer reminder = CreateInteger();
                    result = Div(num1,num2,reminder);
                    if (result != NULL && reminder != NULL){
                        printf("result= ");
                        PrintInteger(result);
                        printf("reminder= ");
                        PrintInteger(reminder);
                        fPrintInteger(result,0);
                        fPrintInteger(reminder,1);
                    }
                    break;
            case 7: printf("Good Bye :)\n");
                    break;
            default: printf("Please choose valid operation\n");
        }
    }
    return 1211553;
}

ListOfInteger readFile (){
    FILE* fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Failed to open file\n");
        exit(1);
    }

    ListOfInteger list = CreateList();

    int c = getc(fp);
    while (c != EOF) {
        // Ignore leading ' ' & '\n' & '\t'
        while (c == ' ' || c == '\t' || c == '\n')
            c = getc(fp);

        // Create a new integer and add its digits to its linked list
        Integer integer = CreateInteger();
        if (c=='-'){
            // if digit equal '-' store 1 at head (1 mean negative number) and get next char
            integer->Data=1;
            c = getc(fp);
        }
        else if (c=='+'){
            // if digit equal '+' store 0 at head (0 mean positive number) and get next char
            integer->Data=0;
            c = getc(fp);
        }
        else
            // if digit equal number make sign positive by default
            integer->Data=0;

        while (c >= '0' && c <= '9') {
            // while read char equal number add to Integer
            AddDigitAtBeginning(c - '0', integer);
            c = getc(fp);
        }
        // store integer to list of integers
        AddInteger(integer, list);
    }

    // indexing all Integer read from file
    Pos ptr = list->Next;
    for (int i=1 ; ptr!=NULL ;i++){
        ptr->count=i;
        ptr=ptr->Next;
    }

    fclose(fp);
    return list;
}

int PrintMenu(){
    // print menu
    printf("\nPlease choose operation:\n");
    printf("1- Read numbers from file\n");
    printf("2- Show all numbers\n");
    printf("3- ADD\n");
    printf("4- Subtract\n");
    printf("5- Multiply\n");
    printf("6- Divide\n");
    printf("7- Exit\n");
    int operation = 0 ;
    // read operation from user
    scanf("%d",&operation);
    return operation;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//                              DoubleLinkedList
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

Integer CreateInteger (){
    // create new node
    Integer L = (Integer)malloc(sizeof(struct nodeContainDigit));
    if(L == NULL)
        printf("Out of memory!\n");
    // new node will be head and points to null
    L->Next = NULL;
    L->Prev = NULL;
    return L;
}

void AddDigitAtBeginning (int Data , Integer L){
    // create new node
    Digit newNode = (Digit)malloc(sizeof(struct nodeContainDigit));
    // save data at new node
    newNode->Data = Data;
    // make new node first node
    newNode->Next = L->Next;
    newNode->Prev = L;
    // if double linked list be empty don't need to make Prev equal new node
    if (L->Next != NULL)
        L->Next->Prev = newNode;

    L->Next = newNode;
}


void AddDigitAtEnd (int Data , Integer L){
    // create new node
    Digit newNode = (Digit)malloc(sizeof(struct nodeContainDigit)) ,ptr = L;
    // save data at new node
    newNode->Data = Data;
    newNode->Next = NULL;

    // find the final node to add after
    while (ptr->Next != NULL)
        ptr =ptr->Next;

    // add after final node
    ptr->Next=newNode;
    newNode->Prev = ptr ;
}

void PrintInteger(Integer L){
    Digit P = L;
    if( L->Next == NULL)
        printf("Empty Integer\n");
    else {
        // print the sign of number
        if(L->Data==0 && P->Next->Data!=0)
            printf("+");
        else  if(L->Data==1&& P->Next->Data!=0)
            printf("-");
        do {
            // will P not equal Null continent
            P = P->Next;
            printf("%d", P->Data);
        } while (P->Next != NULL);
    }
    printf("\n");
}

void fPrintInteger(Integer num,int ResOrReminder){
    FILE* ptrFile = fopen("output.txt","a");
    Digit P = num;
    if( num->Next == NULL)
        printf("Empty Integer\n");
    else {

        // if ResOrReminder=1 that mean print reminder else print result
        if (ResOrReminder)
            fprintf(ptrFile,"Reminder= ");
        else
            fprintf(ptrFile,"Result= ");

        // print the sign of number
        if(num->Data==0 && P->Next->Data!=0)
            fprintf(ptrFile,"+");
        else  if(num->Data==1&& P->Next->Data!=0)
            fprintf(ptrFile,"-");

        do {
            // will ptr not equal head continent
            P = P->Next;
            fprintf(ptrFile,"%d", P->Data);
        } while (P->Next != NULL);
    }
    fprintf(ptrFile,"\n");
    fclose(ptrFile);
}

void PrintIntegerPrev(Integer L){
    // ptr will be pointer for final node
    Digit ptr = LastNode(L);
    if( L->Next == NULL)
        printf("Empty Integer\n");
    else {
        // print the sign of number
        if(L->Data==0 && ptr->Data!=0)
            printf("+");
        else  if(L->Data==1&& ptr->Data!=0)
            printf("-");
        do {
            // will ptr not equal head continent
            printf("%d", ptr->Data);
            ptr = ptr->Prev;
        } while (ptr != L);
    }
    printf("\n");
}

Integer length(Integer L){
    Digit temp = L->Next;
    // create Integer equal zero to save length & Integer equal one to increment count
    Integer count = CreateInteger() , one = CreateInteger();
    AddDigitAtBeginning(0,count);
    AddDigitAtBeginning(1,one);
    count->Data=0;
    one->Data=0;

    // while temp pointer don't reach final node increment count
    while (temp != NULL){
        count= Add(count,one);
        temp=temp->Next;
    }

    return count ;
}

Digit LastNode (Integer L){
    Digit ptr = L;

    // pass all element to find last node
    while (ptr->Next != NULL)
        ptr = ptr->Next;

    return ptr;
}

Integer MakeCopy(Integer num){
    // create new double linked list
    Integer res = CreateInteger();
    // copy the sign
    res->Data=num->Data;
    Digit temp = num->Next;
    // copy each digit from parameter to new double linked list
    while (temp != NULL) {
        AddDigitAtEnd(temp->Data, res);
        temp = temp->Next;
    }
    return res ;
}

void reverse(Integer L) {
    Digit current = L->Next;
    Digit temp = NULL;
    int flag = 1 ;

    // return if null linked list
    if (current == NULL || current->Next == NULL)
        return ;

    while (current != NULL) {
        // exchange pointer for each node
        temp = current->Prev;
        current->Prev = current->Next;
        current->Next = temp;
        if (flag){
            // if it first node the next equal null because it became last node
            flag--;
            current->Next = NULL ;
        }
        // continue to next node
        current = current->Prev;
    }

    // connect the first node (final node) with head
    if (temp != NULL) {
        L->Next = temp->Prev;
        L->Next->Prev = L ;
    }
}

int compare(Integer num1, Integer num2) {
    Digit p1 = num1,p2 = num2;

    // this loop to determine the length for linked list
    while (p1->Next != NULL && p2->Next != NULL) {
        p1 = p1->Next;
        p2 = p2->Next;
    }

    if (p1->Next == NULL && p2->Next == NULL) {
        // if two Integer has same length (compare value)
        while (p1->Prev!= NULL){
            // if two digit are equal continue to next digit
            if (p1->Data == p2->Data) {
                p1 = p1->Prev;
                p2 = p2->Prev;
            }
            else if (p1->Data > p2->Data)
                return 1;
            else
                return -1;
        }
        // if all digit are equal return 0
        return 0;
    }
    else if (p1->Next == NULL)
        // if num1 has less number of digit return -1
        return -1;
    else
        // if num1 has less number of digit return 1
        return 1;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//                              SingleLinkedList
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

ListOfInteger CreateList (){
    // create new single linked list and return address of head
    ListOfInteger L = (ListOfInteger)malloc(sizeof(struct nodeContainInteger));
    if(L == NULL)
        printf("Out of memory\n");
    L->Next = NULL;
    return L;
}

void AddInteger (Integer Data,ListOfInteger L){
    // Add new node to end of single linked list and put data at it
    Pos ptr = L;
    Pos temp =  (Pos)malloc(sizeof(struct nodeContainInteger));
    if (temp == NULL)
        printf("Out of memory\n");
    temp->Next = NULL;
    temp->Data = Data ;

    // find the end node to add new node after it
    while (ptr->Next != NULL)
        ptr = ptr->Next;

    ptr->Next = temp ;
}

Integer findInteger (int count , ListOfInteger List){
    // return the Integer has index equal count
    Pos integer = List->Next;
    while (integer!=NULL && integer->count != count)
        integer = integer->Next;
    return integer->Data;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//                              Operations
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

Integer Add(Integer num1 ,Integer num2){
    Integer result = CreateInteger() ,temp;
    int carry = 0 , digit1 , digit2 , sum , digit;

    // This if statement to control about sign
    if (num1->Data==1 && num2->Data==1)
        // if two number negative set the result negative then add
        result->Data=1;
    else if (num1->Data==0 && num2->Data==0)
        // if two number negative set the result negative then add
        result->Data=0;
    else if (num1->Data==0 && num2->Data==1) {
        // if first number positive and the second is negative the res = first num - second num
        temp = CreateInteger();
        // Make the second number positive then pass to sub (without change in real sign)
        temp->Data=0;
        temp->Next=num2->Next;
        return Sub(num1, temp);
    }
    else {
        // if first number negative and the second is positive the res = second num - first num
        temp = CreateInteger();
        // Make the first number positive then pass to sub (without change in real sign)
        temp->Data=0;
        temp->Next=num1->Next;
        return Sub(num2,temp);
    }

    /*                  1
     *  num1=229   9 -> 2 -> 2
     *  num2=32    2 -> 3
     *             -----------  +
     *             1 <- 6 <- 2
     *   node contain 2 will be first node then 6 then 1
     *   Hence result will be 2 -> 6 -> 1
    */

    Digit ptr1 = num1->Next , ptr2 = num2->Next;
    while (ptr1 != NULL || ptr2 != NULL || carry != 0) {

        // if the first number end but the operation in progress set digit1=0
        digit1 = (ptr1 != NULL)? ptr1->Data : 0;
        // if the second number end but the operation in progress set digit2=0
        digit2 = (ptr2 != NULL)? ptr2->Data : 0;

        // find the sum of digit and calculate 1-digit insert to res 2-carry
        sum = digit1 + digit2 + carry;
        carry = sum / 10;
        digit = sum % 10;
        AddDigitAtBeginning(digit, result);

        // increment pointer if pointer not equal null
        if (ptr1 != NULL)
            ptr1 = ptr1->Next;
        if (ptr2 != NULL)
            ptr2 = ptr2->Next;
    }

    return result;
}

Integer Sub(Integer num1, Integer num2) {
    Integer result = CreateInteger(),ptr;
    int borrow = 0 ,diff ,digit1,digit2,flag=compare(num1,num2);

    // This if statement to control about sign
    if (num1->Data==1 && num2->Data==1){
        if (flag==0 || flag==1)
            // if two number be negative and num1 larger than num2 res negative  -A - -B = -(A - B)
            result->Data=1;
        else {
            // if two number be negative and num2 larger than num1 res positive  -A - -B = +(B - A)
            ptr = num2 ;
            num2 = num1;
            num1 = ptr;
            result->Data = 0;
        }
    }
    else if (num1->Data==0 && num2->Data==0){
        if (flag==0 || flag==1)
            // if two number be positive and num1 larger than num2 res negative  A - B = +(A - B)
            result->Data=0;
        else {
            // if two number be positive and num1 larger than num2 res negative  A - B = -(B - A)
            ptr = num2 ;
            num2 = num1;
            num1 = ptr;
            result->Data = 1;
        }
    }
    else if (num1->Data==1 && num2->Data==0) {
        // if num1 be negative & num2 is positive res negative and add num1,num2  -A - B = -(A+B)
        ptr = CreateInteger();
        ptr->Data=1;
        ptr->Next=num2->Next;
        return Add(num1, ptr);
    }
    else {
        // if num2 be negative & num1 is positive res positive and add num1,num2  A - -B = +(A+B)
        ptr = CreateInteger();
        ptr->Data=0;
        ptr->Next=num2->Next;
        return Add(ptr,num1);
    }

    /*                        1
     *   num1=229   9 -> 2 -> 2
     *   num2=32    2 -> 3
     *              -----------  -
     *              7 <- 9 <- 1
     *   node contain 1 will be first node then 9 then 7
     *   Hence result will be 1 -> 9 -> 7
     */


    Digit ptr1=num1->Next , ptr2 = num2->Next;
    while (ptr1 != NULL || ptr2 != NULL) {

        // if the first number end but the operation in progress set digit1=0
        digit1 = (ptr1 != NULL) ? ptr1->Data : 0;
        // if the second number end but the operation in progress set digit2=0
        digit2 = (ptr2 != NULL) ? ptr2->Data : 0;

        // Subtract the digits and the borrow
        diff = digit1 - digit2 - borrow;

        // If the difference is negative, borrow from the next higher digit
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        AddDigitAtBeginning(diff, result);

        // increment pointer if pointer not equal null
        if (ptr1 != NULL)
            ptr1 = ptr1->Next;
        if (ptr2 != NULL)
            ptr2 = ptr2->Next;
    }

    // Removing leading zero from result
    while (result->Next->Data == 0 && result->Next->Next != NULL) {
        Digit temp = result->Next;
        result->Next = temp->Next;
        temp->Next->Prev = result;
        free(temp);
    }

    return result;
}

Integer Mul(Integer num1, Integer num2) {
    Integer result = CreateInteger();
    // calculate the size of result
    Integer size = Add(length(num1) , length(num2));
    // declare count equal zero and declare number equal 1
    Integer count = CreateInteger() , one = CreateInteger();
    AddDigitAtBeginning(0,count);
    AddDigitAtBeginning(1,one);
    count->Data=0;
    one->Data=0;

    // initialize result to zero
    while (compare(count,size)==-1){
        AddDigitAtBeginning(0, result);
        count = Add(count,one);
    }

    // This if statement to control about sign
    if (num1->Data == num2->Data)
        result->Data=0;
    else
        result->Data=1;

    /*
     *   num1=229   9 -> 2 -> 2
     *   num2=32    2 -> 3
     *   the max size of res equal 5
     *   then res =  0  ->  0  ->  0  ->  0  ->  0
     *              xA     xB     xC     xD     xE
     *
     *   initial res1 = xA & ptr2 to first digit from num2
     *   now 2(ptr2->Data) * 9 -> 2 -> 2 = 8 -> 5 -> 4  add to res
     *   then res =  8  ->  5  ->  4  ->  0  ->  0
     *   address    xA     xB     xC     xD     xE
     *
     *   increment res1 = xB & ptr2 to second digit from num2 & res2=res1
     *   now 3 * 9 = 27 + 0 + 5(xB) = 32 then store 2 at res2 and carry = 3 and increment res2
     *   now 3 * 2 = 6 + 3 + 4(xC) = 13 then store 3 at res2 and carry = 1 and increment res2
     *   now 3 * 2 = 6 + 1 + 0(xD) = 7 then store 7 at res2 and carry = 0 and increment res2
     *   then res =  8  ->  2  ->  3  ->  7  ->  0
     *              xA     xB     xC     xD     xE
     *   reverse the res and remove leading 0
     *   then res = 7 -> 3 -> 2 -> 8
     */

    Digit ptr1 , ptr2 = num2->Next, res1 = result->Next , res2;
    int carry , mul;
    while (ptr2 !=NULL){
        // outer loop for passing through digit for num2
        carry = 0 ;
        res2 = res1 ;           // res2 is pointer to where add
        ptr1 = num1->Next;      // ptr1 is pointer to first digit

        while (ptr1 != NULL){
            // inner loop for passing through digit for num1
            mul = ptr1->Data * ptr2->Data + carry + res2->Data ;
            res2->Data = mul%10 ;
            carry = mul/10 ;
            res2 = res2->Next;
            ptr1 = ptr1->Next;
        }
        if (carry>0)
            // if we have carry add to result
            res2->Data = carry ;
        // increment pointer
        res1 = res1->Next;
        ptr2 = ptr2->Next;
    }
    // reverse the result
    reverse(result);

    // remove leading zero from the result
    while (result->Next->Data==0){
        ptr1 = result->Next;
        result->Next=ptr1->Next;
        result->Next->Prev=result;
        free(ptr1);
        if (result->Next->Next == NULL)
            break;
    }

    return result;
}

Integer Div(Integer num1, Integer num2,Integer Rem) {
    Integer result = CreateInteger();
    // declare number equal 0
    Integer zero = CreateInteger();
    AddDigitAtBeginning(0,zero);

    if (compare(num2,zero) == 0){
        // check if divide by zero
        printf("div by zero");
        return NULL;
    }
    else if(compare(num1,num2)==-1){
        // check if divisor larger than dividend
        AddDigitAtBeginning(0,result);
        Integer Copy = MakeCopy(num1);
        Rem->Next =Copy->Next;
        Copy->Next->Prev = Rem;
        Rem->Data=num1->Data;
        reverse(Rem);
        return result ;
    }

    // This if statement to control about sign
    if (num1->Data == num2->Data)
        result->Data=0;
    else
        result->Data=1;

    /*
     *      long division:                        result
     *                                       ----------------
     *                            divisor   |    dividend
     *                          ------------  digit * divisor
     *                                        ---------------
     *                                            reminder
     *   num1=229   9 -> 2 -> 2
     *   num2=10    0 -> 1                         2 -> 2
     *                                       ----------------
     *                            0 -> 1    |   9 -> 2 -> 2
     *                          ------------         0 -> 2
     *                                        ---------------
     *                                          9 <- 2
     *                                          0 -> 2
     *                                        ---------------
     *                                          9
     */

    // create Integer to contain how many digit from dividend divisible by divisor
    Integer reminder = CreateInteger();
    reminder->Data=0;
    Digit ptr1 = LastNode(num1);
    while (compare(reminder,num2) == -1) {
        AddDigitAtBeginning(ptr1->Data,reminder);
        ptr1 = ptr1->Prev;
    }

    // save the sign of num2 and make it positive because we use Sub & Mul
    int sign = num2->Data;
    num2->Data = 0;

    do{
        // determine the value of (reminder / divisor)
        int digitFroRes = 0 ;
        Integer copy = MakeCopy(reminder);
        copy->Data=0 ;
        while(compare(copy,num2) >= 0){
            copy = Sub(copy,num2);
            reverse(copy);
            digitFroRes++;
        }

        // save the value of (reminder / divisor) to result
        AddDigitAtBeginning(digitFroRes,result);
        // create Integer has value equal (reminder / divisor)
        Integer temp = CreateInteger();
        AddDigitAtBeginning(digitFroRes,temp);
        temp->Data=0;
        // multiply (reminder / divisor) by num2
        Integer mul = Mul(temp,num2);
        mul->Data=0;
        reverse(mul);
        // find the new value of reminder
        reminder = Sub(reminder,mul);
        reverse(reminder);
        // LastReminder: use as key for if the reminder < num2 after add digit from num1 to reminder add zero to result
        int LastReminder = 0;

        if (compare(reminder,zero) == 0 && ptr1 != num1 && ptr1->Data!=0){
            // if the reminder equal zero exchange zero by new digit (new digit not equal zero)
            reminder->Next->Data=ptr1->Data;
            LastReminder++;
            ptr1=ptr1->Prev;
        }
        else if (compare(reminder,zero) == 1 && ptr1 != num1){
            // if the reminder not equal zero add new digit
            AddDigitAtBeginning(ptr1->Data,reminder);
            LastReminder++;
            ptr1=ptr1->Prev;
        }

        while (ptr1 != num1 && compare(reminder,zero) == 0 && ptr1->Data==0){
            // while reminder equal zero and digit in dividend equal zero add zero to result
            AddDigitAtBeginning(0,result);
            ptr1=ptr1->Prev;
        }

        if (ptr1 != num1 && compare(reminder,zero) == 0 && ptr1->Data !=0){
            // after pass all zeros in previous step
            // if the reminder still zero exchange zero by new digit (new digit not equal zero)
            reminder->Next->Data=ptr1->Data;
            LastReminder++;
            ptr1=ptr1->Prev;
        }

        while (compare(reminder,num2) == -1 && ptr1 != num1) {
            // if the reminder still < num2 add digit to reminder and add zero to result
            AddDigitAtBeginning(0,result);
            AddDigitAtBeginning(ptr1->Data,reminder);
            ptr1 = ptr1->Prev;
            LastReminder++;
        }

        if (!(compare(reminder,num2) >=0)  && LastReminder)
            // reminder < num2 after add all digit from num1 add zero
            AddDigitAtBeginning(0,result);

    } while (compare(reminder,num2) >=0 );

    // return reminder
    Rem->Next=reminder->Next;
    reminder->Next->Prev=Rem;
    // the sign of reminder same as sign for dividend
    Rem->Data=num1->Data;
    // return the sign for num2 (if we want to do another operation)
    num2->Data = sign;
    reverse(Rem);
    reverse(result);
    return result ;
}