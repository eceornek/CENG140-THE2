#include <stdio.h>
#include <stdlib.h>

char *initial_seq;
char *left_seq;
char *right_seq;
char *curpos;
int isLeft=1;
int axiom=1;

int main(){
    void compactify_string(char *s);
    int isLetter(char c);
    int isNegativeLetter(char c);
    int match_par(char *s, int k);
    int match_square(char *s, int k);
    int r_match_par(char *s, int k);
    int r_match_square(char *s, int k);
    int end_of_string(char* s);
    void right_comparison(char *c);
    void wang_proven();

    char *s;
    char *c;
    char *initial_right;
    int new_size;
    /*depolama*/
    initial_seq = malloc(200*sizeof(char));
    scanf("%s", initial_seq);

    for (s=initial_seq;*s;s++) {
        if (*s=='#'){
            initial_right=(s+1);
        }
    }
    new_size=s-initial_seq+1;
    initial_seq=realloc(initial_seq,new_size);

    left_seq = malloc(200*sizeof(char));
    right_seq = malloc(200*sizeof(char));

    c=left_seq;
    for (s=initial_seq;*s!='#';s++,c++){
        *c=*s;
    }
    *c=0;
    c=right_seq;
    for (s=initial_right;*s;s++,c++){
        *c=*s;
    }
    *c=0;
    /*depolama*/

    for (s=left_seq;*s;s++){
        if (*s=='>'){
            if (isLetter(*(s-1))){
                *(s-1)+=32;
            }
            else if (*(s-1)==')'){
                *(s-1)=']';
                *(left_seq + r_match_par(left_seq, s-1-left_seq))='[';
            }
            *s='|';
        }
    }
    for (s=right_seq;*s;s++){
        if (*s=='>'){
            if (isLetter(*(s-1))){
                *(s-1)+=32;
            }
            else if (*(s-1)==')'){
                *(s-1)=']';
                *(right_seq + r_match_par(right_seq, s-1-right_seq))='[';
            }
            *s='|';
        }
    }
    for (s=left_seq;*s;s++){
        if (*s=='-'&&*(s+1)=='-'){
            *s=' ';
            *(s+1)=' ';
            compactify_string(left_seq);
            s--;
        }
    }
    for (s=right_seq;*s;s++){
        if (*s=='-'&&*(s+1)=='-'){
            *s=' ';
            *(s+1)=' ';
            compactify_string(right_seq);
            s--;
        }
    }

    for (s=left_seq;*s;s++){
        if (*s=='-'){
            c=s+1;
            if (isLetter(*c)){
                *c+=32;
            }
            else if (isNegativeLetter(*c)){
                *c-=32;
            }
            else if (*(s+1)=='('){
                *c='[';
                *(left_seq + match_par(left_seq,c-left_seq))=']';
            }
            else if (*c=='['){
                *c='(';
                *(left_seq + match_square(left_seq,c-left_seq))=')';
            }
            *s=' ';
            compactify_string(left_seq);
        }
    }
    
    for (s=right_seq;*s;s++){
        if (*s=='-'){
            c=s+1;
            if (isLetter(*c)){
                (*c)+=32;
            }
            else if (isNegativeLetter(*c)){
                (*c)-=32;
            }
            else if (*c=='('){
                *c='[';
                *(right_seq + match_par(right_seq,c-right_seq))=']';
            }
            else if (*c=='['){
                *c='(';
                *(right_seq + match_square(right_seq,c-right_seq))=')';
            }
            *s=' ';
            compactify_string(right_seq);
        }
    }
    curpos=left_seq;
    wang_proven();
    free(left_seq);
    free(right_seq);
    free(initial_seq);
return 0;
}

void wang_proven(){
    void compactify_string(char *s);
    int isLetter(char c);
    int isNegativeLetter(char c);
    int match_par(char *s, int k);
    int match_square(char *s, int k);
    int end_of_string(char* s);
    void right_comparison(char *c);
    char *c;
    char *s;
    char *es_par;
    char k;

    if (*curpos=='('){
        if (isLeft){
            es_par=left_seq + match_par(left_seq, curpos-left_seq);
            k=*(es_par+1);
            if (k==','||k==0){
                *curpos=' ';
                *es_par=' ';
                compactify_string(left_seq);
            }
            else if (*(es_par+1)=='&'){
                *(es_par+1)=',';
            }
            else if (*(es_par+1)=='|'){
                *(es_par+1)=',';
                axiom++;
                for (s=es_par+2;*s;s++){
                    if (*s==','){
                        right_comparison(s);
                        break;
                    }
                }
            }
        }
        else{
            es_par=right_seq + match_par(right_seq, curpos-right_seq);
            k=*(es_par+1);
            if (k==','||k==0){
                *curpos=' ';
                *es_par=' ';
                compactify_string(right_seq);
            }
            else if (k=='&'){
                *(es_par+1)=',';
                axiom++;
                for (s=es_par+2;*s;s++){
                    if (*s==','){
                        right_comparison(s);
                        break;
                    }
                }
            }
            else if (k=='|'){
                *(es_par+1)=',';
            }
        }
        wang_proven();
    }

    else if ((*curpos)=='['){
        if (isLeft){
            es_par=left_seq + match_square(left_seq, curpos-left_seq);
            k=*(es_par+1);
            if (k==','){
                if (*right_seq!=0){
                    c=right_seq+end_of_string(right_seq);
                    *c++=',';
                }
                else if (*right_seq==0){
                    c=right_seq;
                }
                *curpos=' ';
                for (s=curpos+1;s<es_par;s++,c++){
                    *c=*s;
                    *s=' ';
                }
                *c=0;
                *es_par=' ';
                *(es_par+1)=' ';
                compactify_string(left_seq);
            }
            else if (k==0){
                if (*right_seq!=0){
                    c=right_seq+end_of_string(right_seq);
                    *c++=',';
                }
                else if (*right_seq==0){
                    c=right_seq;
                }
                *curpos=' ';
                for (s=curpos+1;s<es_par;s++,c++){
                    *c=*s;
                    *s=' ';
                }
                c=0;
                *es_par=' ';
                if (curpos!=left_seq){
                    *(curpos-1)=' ';
                    curpos--;
                }
                compactify_string(left_seq);
            }
            else if (k=='&'){
                *(es_par+1)=',';
            }
            else if (k=='|'){
                *(es_par+1)=',';
                axiom++;
                for (s=es_par+2;*s;s++){
                    if (*s==','){
                        right_comparison(s);
                        break;
                    }
                }
            }
        }
        else{
            es_par=right_seq + match_square(right_seq, curpos-right_seq);
            k=*(es_par+1);
            if (k==','){
                if (*left_seq!=0){
                    c=left_seq+end_of_string(left_seq);
                    *c++=',';
                }
                else if (*left_seq==0){
                    c=left_seq;
                }
                *curpos=' ';
                for (s=curpos+1;s<es_par;s++,c++){
                    *c=*s;
                    *s=' ';
                }
                *c=0;
                *es_par=' ';
                *(es_par+1)=' ';
                compactify_string(right_seq);
            }
            else if (k==0){
                if (*left_seq!=0){
                    c=left_seq+end_of_string(left_seq);
                    *c++=',';
                }
                else if (*left_seq==0){
                    c=left_seq;
                }
                *curpos=' ';
                for (s=curpos+1;s<es_par;s++,c++){
                    *c=*s;
                    *s=' ';
                }
                *c=0;
                *es_par=' ';
                if (curpos!=right_seq){
                    *(curpos-1)=' ';
                    curpos--;
                }
                compactify_string(right_seq);
            }
            else if (k=='&'){
                *(es_par+1)=',';
                axiom++;
                for (s=es_par+2;*s;s++){
                    if (*s==','){
                        right_comparison(s);
                        break;
                    }
                }
            }
            else if (k=='|'){
                *(es_par+1)=',';
            }
        }
        wang_proven();
    }
    else if (isLetter(*curpos)){
        k=*(curpos+1);
        if (k==','){
            curpos+=2;
        }
        else if (k==0){
            curpos++;
        }
        else if (k=='&'){
            *(curpos+1)=',';
            if (!isLeft){
                axiom++;
                for (s=curpos+2;*s;s++){
                    if (*s==','){
                        right_comparison(s);
                        break;
                    }
                }
            }
        }
        else if (k=='|'){
            *(curpos+1)=',';
            if (isLeft){
                axiom++;
                for (s=curpos+2;*s;s++){
                    if (*s==','){
                        right_comparison(s);
                        break;
                    }
                }
            }
        }
        wang_proven();
    }
    else if (isNegativeLetter(*curpos)){
        k=*(curpos+1);
        if (k==','){
            if (isLeft){
                if (*right_seq!=0){
                    c=right_seq+end_of_string(right_seq);
                    *c++=',';
                    *c++=((*curpos)-32);
                    *c=0;
                    *curpos=' ';
                    *(curpos+1)=' ';
                    compactify_string(left_seq);
                }
                else{
                    c=right_seq;
                    *c++=((*curpos)-32);
                    *c=0;
                    *curpos=' ';
                    *(curpos+1)=' ';
                    compactify_string(left_seq);
                }
            }
            else{
                if (*left_seq!=0){
                    c=left_seq+end_of_string(left_seq);
                    *c++=',';
                    *c++=((*curpos)-32);
                    *c=0;
                    *curpos=' ';
                    *(curpos+1)=' ';
                    compactify_string(right_seq);
                }
                else {
                    c=left_seq;
                    *c++=((*curpos)-32);
                    *c=0;
                    *curpos=' ';
                    *(curpos+1)=' ';
                    compactify_string(right_seq);
                }               
            }
        }
        else if (k==0){
            if (isLeft){
                if (*right_seq!=0){
                    c=right_seq+end_of_string(right_seq);
                    *c++=',';
                    *c++=((*curpos)-32);
                    *c=0;
                    *curpos=' ';
                    if (curpos!=left_seq){
                        *(curpos-1)=' ';
                        curpos--;
                    }
                    compactify_string(left_seq);
                }
                else {
                    c=right_seq;
                    *c++=((*curpos)-32);
                    *c=0;
                    *curpos=' ';
                    if (curpos!=left_seq){
                        *(curpos-1)=' ';
                        curpos--;
                    }
                    compactify_string(left_seq);
                }
            }
            else{
                if (*left_seq!=0){
                    c=left_seq+end_of_string(left_seq);
                    *c++=',';
                    *c++=((*curpos)-32);
                    *c=0;
                    *curpos=' ';
                    if (curpos!=right_seq){
                        *(curpos-1)=' ';
                        curpos--;
                    }
                    compactify_string(right_seq);
                }
                else {
                    c=left_seq;
                    *c++=((*curpos)-32);
                    *c=0;
                    *curpos=' ';
                    if (curpos!=right_seq){
                        *(curpos-1)=' ';
                        curpos--;
                    }
                    compactify_string(right_seq);
                }                   
            }
        }
        else if (k=='&'){
            *(curpos+1)=',';
            if (!isLeft){
                axiom++;
                for (s=curpos+2;*s;s++){
                    if (*s==','){
                        right_comparison(s);
                        break;
                    }
                }
            }
        }
        else if (k=='|'){
            *(curpos+1)=',';
            if (isLeft){
                axiom++;
                for (s=curpos+2;*s;s++){
                    if (*s==','){
                        right_comparison(s);
                        break;
                    }
                }
            }
        }
        wang_proven();
    }
    else if ((*curpos)==0){
        if (isLeft){
            curpos = right_seq;
            isLeft=0;
            wang_proven();
        }
        else{
            /*comparison and result*/
            for (c=left_seq;*c;c++){
                if (isLetter(*c)){
                    for (s=right_seq;*s;s++){
                        if (isLetter(*s)&&*c==*s){
                            axiom--;
                        }
                    }
                }
            }
            if (axiom<=0){
                printf("T\n");
            }
            else {
                printf("F\n");
            }
            /*comparison and result*/
        }
    }
}

int isLetter(char c){
    if (c>=65 &&c<=90) {
        return 1;
    }
    else {
        return 0;
    }
}

int isNegativeLetter(char c){
    if (c>=97 &&c<=122) {
        return 1;
    }
    else {
        return 0;
    }
}

int match_par(char *s, int k){
    char *start;
    int count;
    start=s;
    for (count=1,s+=k+1;*s;s++){
        switch(*s){
            case '(': 
                count++;
                break;
            case ')':
                count--;
                break;
        }
        if (count==0){
            return s-start;
        }
    }
}

int r_match_par(char *s, int k){
    char *start;
    int count;
    start=s;
    for (count=1,s+=k-1;;s--){
        switch (*s)
        {
        case '(':
            count--;
            break;
        case ')':
            count++;
            break;
        }
        if (count==0){
            return s-start;
        }
    }
}

int match_square(char *s, int k){
    char *start;
    int count;
    start=s;
    for (count=1,s+=k+1;*s;s++){
        switch(*s){
            case '[': 
                count++;
                break;
            case ']':
                count--;
                break;
        }
        if (count==0){
            return s-start;
        }
    }
}

int r_match_square(char *s, int k){
    char *start;
    int count;
    start=s;
    for (count=1,s+=k-1;;s--){
        switch (*s)
        {
        case '[':
            count--;
            break;
        case ']':
            count++;
            break;
        }
        if (count==0){
            return s-start;
        }
    }
}

/* removes white spaces*/
void compactify_string(char *s){
    char *p;
    for (p=s;*s;s++){
        if (*s==' '){
            continue;
        }
        else{
            if (s!=p){
                *p++=*s;
            }
            else{
                p++;
            }           
        }
    }
    *p=0;
}

int end_of_string(char* s){
    char *start;
    start=s;
    for (;;s++){
        if (*s==0){
            return s-start;
        }
    }
}

void right_comparison(char *c){
    int isNegativeLetter(char c);
    int isLetter(char c);
    char *s;
    for (;*c;c++){
        if (isLeft){
            if (isLetter(*c)||isNegativeLetter(*c)){
                for (s=right_seq;*s;s++){
                    if (isLetter(*s)||isNegativeLetter(*s)){
                        if (*c==*s){
                            axiom--;
                        }
                    }    
                }
            }      
        }
        else {
            if (isLetter(*c)||isNegativeLetter(*c)){
                for (s=left_seq;*s;s++){
                    if (isLetter(*s)||isNegativeLetter(*s)){
                        if (*c==*s){
                            axiom--;
                        }
                    }    
                }
            }      
        }
    }
}
