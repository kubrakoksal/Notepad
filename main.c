#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include<conio.h>
COORD coord = {0, 0};


char str[50];
char kyt[50];


int satir=0,sutun=0,max_satir=0,ekran_ust=0,ekran_alt=34,boyut=0;


void gotoxy (int x, int y)
{

    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}


void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}


void showcursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 10;
    info.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &info);
}



struct liste
{

    int data;
    struct liste *next;
    struct liste *prev;
};

typedef struct liste node;

node **ptr;
node *kayit;
node * ekleme;
node * root;
node * kopyalayedek;
void karakter_sil();
void yontuslari(int);
void yazi();
void enter();
void karakter_ekle();
int menu();
void kaydet();
void farkli_kaydet();
void kaydetmekapat();
void kopyala();
void yapistir();
void dosya_ac();
void kes(int,int);
void yapistir();
int kayitet=0;
int dosyaac=0;
int cikisbas=0;
int kayiteleman=0;
int kesyaz=0;

int main()
{
    SetConsoleTitle("NOTEPAD");
    ekleme=malloc(sizeof(node));
    ptr=(node**)malloc(sizeof(node*)*10000);
    int j;
    for(j=0; j<10000; j++)
    {
        ptr[j]=NULL;
    }

    root=(node*)malloc(sizeof(node));

    root->next=NULL;
    root->prev=NULL;
    int shift=0;
    while(1)
    {
        root->data=_getch();
        if(GetKeyState(VK_SHIFT)<0)
            shift=1;
        else
            shift=0;


        int a;
        if(root->data==0)
        {

            a=menu();
        }
        if(shift==1&&root->data==224&&ptr[0]!=NULL)
        {
            kopyala();
        }
        else  if(shift==0&&(root->data==224 || root->data==0))
            {yontuslari(a);}
        else if(shift==0&&root->data==22&&kayiteleman!=0)
        {
            yapistir();
            kayitet=0;

        }
        else if(shift==0&&((root->data>=65 && root->data<=90)||(root->data>=91 && root->data<=125)||(root->data>=32 && root->data<=63)))
        {
               yazi();
                kayitet=0;
        }
        else if(shift==0&&(root->data==13))
        {enter();
        kayitet=0;}
        else if(shift==0&&(root->data==8))
        {karakter_sil();
        kayitet=0;}
        else if(shift==0&&(root->data==27))
        {
            if(kayitet==0){a=menu();
           if(a==-1){system("cls");
             exit(0);

                    }
            }
            else {

                system("cls");
             exit(0);

            }

        }
    }

    return 0;
}

void kopyala()
{


    kayit=(node*)malloc(sizeof(node));
    kayit->next=NULL;
    kayit->prev=NULL;
     int kessatir=satir,kessutun=sutun;
    int kac=0;

    int i;
    node * head=ptr[satir];
    for(i=0;i<sutun;i++)
    {
        head=head->next;
    }

    if(satir==max_satir&&ptr[satir]==NULL)
       {head=root;
       }
    node * renkdegistir=head;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),116);
   if(head!=root&&head->data!=10) printf("%c",head->data);
   else if(head==root||head->data==10){printf(" ");
    gotoxy(sutun,satir);
   }


    int shift=1;

    int a=0;
    int elemanal;
    int gecicisutun=sutun,gecicisatir=satir;
    while(shift==1)
    {
           int kesal=0;
        if(a!=0)elemanal=_getch();
        a++;
        elemanal=_getch();
        if(GetKeyState(VK_SHIFT)<0)
            shift=1;
        else
            shift=0;
            node * sil;
        if(shift==0)
        {

            if(kayit->prev==NULL&&kayit->next==NULL);
            else if(kayit->next==NULL)
            {
                sil=kayit;
                kayit=kayit->prev;
                kayit->next=NULL;

            }
            else if(kayit->prev==NULL)
            {
                sil=kayit;
                kayit=kayit->next;
                kayit->prev=NULL;
                free(sil);
                sutun=gecicisutun;
                satir=gecicisatir;
            }
            gotoxy(gecicisutun,gecicisatir);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
           if(renkdegistir!=root&&renkdegistir->data!=10) printf("%c",renkdegistir->data);
             else if(renkdegistir==root||renkdegistir->data==10)printf(" ");
             gotoxy(gecicisutun,gecicisatir);
            break;

        }

        if(elemanal==75&&head!=ptr[0])
        {
            if(kayit->prev==NULL)
            {
                kayit->data=head->prev->data;
                kayit->prev=malloc(sizeof(node));
                kayit->prev->next=kayit;
                kayit=kayit->prev;
                kayit->prev=NULL;
                kac++;
                kesal=1;

            }
            else
            {  node * sil;
            if(kac==1)
                {
                  sil=kayit;
                   kayit->prev->next=NULL;
                   kayit=kayit->prev;
                   free(sil);

                }
            else{
                sil=kayit->prev;
                kayit->prev->prev->next=kayit;
                kayit->prev=kayit->prev->prev;


            }
            free(sil);
                kac--;
            }
            head=head->prev;
            sutun--;
            if(sutun==-1)
            {
                if(satir>=1)
                {
                    satir--;
                    node * x=ptr[satir];
                    int sayi=0;
                    while(x->data!=10)
                    {
                        sayi++;
                        x=x->next;
                    }
                    if(sayi==70)
                        sutun=69;
                    else
                        sutun=sayi;
                }
            }
            if(kesal==1)
            {
                kessutun=sutun;
                kessatir=satir;
            }
            gotoxy(sutun,satir);

        }
        else if(elemanal==77&&head!=root)
        {
            if(kayit->next==NULL)
            {
                kayit->data=head->data;
                kayit->next=malloc(sizeof(node));
                kayit->next->prev=kayit;
                kayit=kayit->next;
                kayit->next=NULL;
                kac++;
            }
            else
            {
                node * sil;
              if(kac==1)
                {
                  sil=kayit;
                   kayit->next->prev=NULL;
                   kayit=kayit->next;
                   free(sil);

                }
            else{
                sil=kayit->next;
                kayit->next->next->prev=kayit;
                kayit->next=kayit->next->next;


            }
                free(sil);
                kac--;
                kesal=1;


            }

            head=head->next;


            int i;

            node * say=ptr[satir];
            for(i=0;i<sutun;i++)
            {
                say=say->next;
            }

            if(say!=root&&say!=NULL)
            {
                if(say->data==10)
                {
                    satir++;
                    sutun=0;

                }

               else if(say->data!=10)
               {
                   sutun++;
               }


            }

            if(kesal==1)
                 {

                    kessatir=satir;
                    kessutun=sutun;

                 }
              gotoxy(sutun,satir);

        }
    }


    int control=0,escape=0;
    while(escape==0&&control==0)
    {

        if(GetKeyState(VK_ESCAPE)<0)
            escape=1;
        else
            escape=0;
        if(GetKeyState(VK_CONTROL)<0)
            control=1;
        else
            control=0;


    }
    if(escape==1)
    {
       node *x;
       _getch();
       if(kayit->next==NULL)
       {
           while(kayit!=NULL)
           {
               x=kayit->prev;
               free(kayit);
               kayit=x;

           }


       }
       else if(kayit->prev==NULL)
       {

             while(kayit!=NULL)
           {
               x=kayit->next;
               free(kayit);
               kayit=x;

           }

       }

    }
    else if(control==1)
    {
       elemanal=_getch();

       if(elemanal==3||elemanal==24)
        {
       kopyalayedek=kayit;
        kayiteleman=kac;


       if(elemanal==24)
       {

           kes(kessatir,kessutun);
       }



        }
     else  {

            node *c;
       if(kayit->next==NULL)
       {
           while(kayit!=NULL)
           {
               c=kayit->prev;
               free(kayit);
               kayit=c;

           }


       }
       else if(kayit->prev==NULL)
       {

             while(kayit!=NULL)
           {
               c=kayit->next;
               free(kayit);
               kayit=c;

           }

       }

        }
    }





}


void yapistir()
{


     if(kopyalayedek->next!=NULL)
     {
         while(kopyalayedek->next!=NULL)
         {

            kopyalayedek=kopyalayedek->next;

         }

     }


     node * geciciyedek=kopyalayedek;
     int i;
     int gecicisatir=satir;
     int gecicisutun=sutun;
     for(i=1;i<=kayiteleman;i++)
       {
           root->data=kopyalayedek->data;
           satir=gecicisatir;
           sutun=gecicisutun;
           yazi();
           kopyalayedek=kopyalayedek->prev;

       }

     kopyalayedek=geciciyedek;




}

int menu()
{


    int x;
    if(root->data==0)
    x=_getch();
    else x=59;

    if(x==59)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),116);
        system("cls");
        gotoxy(14,8);
        printf("_______________SECENEKLER_______________");
        gotoxy(13,22);
        printf("_________________________________________");

        int i;
        for(i=9; i<23; i++)
        {
            gotoxy(13,i);
            printf("|");
            gotoxy(54,i);
            printf("|");

        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),114);
        gotoxy(25,14);
        printf("--->");




        if(root->data!=0)gotoxy(30,12);
        if(root->data!=0)printf("KAYDETME");
        gotoxy(30,14);
        printf("KAYDET");
       if(root->data!=27) gotoxy(30,16);
        if(root->data!=27)printf("FARKLI KAYDET");
        if(root->data!=27)gotoxy(30,18);
        if(root->data!=27)printf("DOSYA AC");
        hidecursor();
        int asatir=14;
        int var=0;
        while(1)
        {

            int a=_getch();

            if(var==0&&(a==0||a==224))
            {

                a=_getch();
                 if(a==80)
                {
                    gotoxy(25,asatir);
                    printf("    ");
                    asatir+=2;
                    if(asatir==20&&root->data==0)
                        asatir=14;
                    else if(asatir==16&&root->data==27)
                        asatir=12;
                    gotoxy(25,asatir);
                    printf("--->");
                }



            }
            else if(a==13&&var==0)
            {

                if(asatir==12)
                    {kaydetmekapat();
                    var=1;}
                else if(asatir==14)
                    {kaydet();
                    if(root->data==27)cikisbas=1;
                    var=1;
                    }
                else if(asatir==16)
                    {farkli_kaydet();
                    var=1;}
                else if(asatir==18&&ptr[0]==NULL)
                    {dosya_ac();
                    break;
                    var=1;
                    }
                    else if(asatir==18&&ptr[0]!=NULL)
                        var=0;

            }
            else if(a==27)
                {

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
        system("cls");
        node *head =ptr[0];
        while(head!=NULL&&head!=root)
        {

            printf("%c",head->data);
            head=head->next;
        }
        showcursor();
        gotoxy(sutun,satir);
        if(root->data==27&&cikisbas==1)
        {
            cikisbas=0;
            return -1;
        }

        break;

                }

        }

    }

    return x;
}

void kaydetmekapat()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
    system("cls");
    exit(0);


}

void dosya_ac()
{

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),116);
    system("cls");
    gotoxy(14,8);
    printf("_________________________________________");
    gotoxy(13,22);
    printf("_________________________________________");

    int i;
    for(i=9; i<23; i++)
    {
        gotoxy(13,i);
        printf("|");
        gotoxy(54,i);
        printf("|");

    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),114);
    gotoxy(16,12);
    printf("    Dosyanin adini giriniz");
    gotoxy(25,15);
    showcursor();
    char dosya[16];
    int a;
    for(i=0; i<15; i++)
    {
        a=_getch();

        if(a==13)
            break;
        else  if(a==27)
            break;
        dosya[i]=a;
        printf("%c",a);
        dosya[i+1]='\0';
        if(i==14)
           a=13;

    }

    if(a==27)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
        system("cls");
        node *head =ptr[0];
        while(head!=NULL&&head!=root)
        {

            printf("%c",head->data);
            head=head->next;
        }
        gotoxy(sutun,satir);


    }
    else if(a==13)
    {
        strcat(dosya,".txt");
        FILE * oku=fopen(dosya,"r");
        if(oku==NULL)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),114);
            gotoxy(16,12);
            printf("Boyle bir dosya yok              ");
            gotoxy(22,15);
            printf(" Cikmak icin ESC ye basiniz ");

        }
        else
        {
            strcpy(kyt,dosya);
            max_satir=0;
            int i=0,var=0;
            while(1)
            {
                char x=fgetc(oku);
                if(x==EOF)
                    break;
                if(i==0)
                {
                    ptr[i]=root;
                    i++;
                }
                else if(var==1)
                {
                    ptr[i]=root;
                    i++;
                    var=0;
                }
                if(x=='\n')
                {
                    var=1;
                    max_satir++;

                }
                root->data=x;
                node * temp=root;
                root->next=malloc(sizeof(node));
                root=root->next;
                root->prev=temp;
                root->next=NULL;


            }

            boyut=i;
            satir=0;
            sutun=0;
            ekran_alt=34;
            ekran_alt=0;

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
            system("cls");

           if(root->prev!=NULL){
            root=ptr[0];
            while(root->next!=NULL)
            {
                printf("%c",root->data);
                root=root->next;

            }

            gotoxy(0,0);
            }

        }


    }








}

void kaydet()
{

    if(strcmp(kyt,"")==0)
        farkli_kaydet();
    else
    {
        FILE * dosya=fopen(kyt,"w+");
        node * head=ptr[0];
        if(ptr[0]==NULL&&strcmp(kyt,"")!=0&&root->data!=27)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),114);
            gotoxy(16,12);
            printf("Dosya bos                            ");
            gotoxy(25,15);
            printf("                          ");
            gotoxy(25,16);
            printf("                          ");
            gotoxy(25,18);
            printf("                          ");
            gotoxy(25,20);
            printf("                          ");

        }
        else
        {
            if(ptr[0]==NULL&&strcmp(kyt,"")!=0)
            {
                dosya=fopen(kyt,"w");
            }
            else
            {

                while(head->next!=NULL&&ptr[0]!=NULL)
                {
                    fputc(head->data,dosya);
                    head=head->next;

                }
            }



            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),116);
            system("cls");
            gotoxy(14,8);
            printf("_________________________________________");
            gotoxy(13,22);
            printf("_________________________________________");

            int i;
            for(i=9; i<23; i++)
            {
                gotoxy(13,i);
                printf("|");
                gotoxy(54,i);
                printf("|");

            }
            hidecursor();
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),114);
            gotoxy(16,12);
            printf("Dosya basariyla kaydedildi");
            kayitet=1;
        }
        gotoxy(16,14);
        printf("Cikmak icin ESC tusuna basiniz        ");

    }


}

void farkli_kaydet()
{

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),116);
    system("cls");
    gotoxy(14,8);
    printf("_________________________________________");
    gotoxy(13,22);
    printf("_________________________________________");

    int i;
    for(i=9; i<23; i++)
    {
        gotoxy(13,i);
        printf("|");
        gotoxy(54,i);
        printf("|");

    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),114);
    gotoxy(16,12);
    printf("Dosya adini giriniz(max. 15 karakter)");
    gotoxy(25,15);
    showcursor();

    int a;
    for(i=0; i<15; i++)
    {
        a=_getch();

        if(a==13)
            break;
        else  if(a==27)
            break;
        str[i]=a;
        str[i+1]='\0';
        printf("%c",str[i]);
        if(i==14)
          a=13;

    }

    if(a==13)
    {
        strcpy(kyt,str);
        strcat(kyt,".txt");
        kaydet();
    }




}

void kes(int kessatir,int kessutun)
{


    int i;
    kesyaz=1;
    for(i=1;i<=kayiteleman;i++)
    {
        satir=kessatir;
        sutun=kessutun;
        karakter_sil();


    }
            system("cls");
         node *  head=ptr[0];
        while(ptr[0]!=NULL&&head->next!=NULL)
        {
            printf("%c",head->data);
            head=head->next;

        }

     gotoxy(sutun,satir);


    kesyaz=0;


}

void enter()
{
    root->data=10;
    node *head;
    int sayi=0;
    head=ptr[max_satir];
    while(head!=NULL)
    {
        sayi++;
        head=head->next;
    }
    if(ptr[0]!=NULL&&((satir==0&&sutun==0)||satir!=max_satir||(satir==max_satir&&sutun+1!=sayi&&ptr[satir]!=NULL)))
    {
        ekleme=root;
        root->prev->next=NULL;
        root=root->prev;
        karakter_ekle();
    }
    else
    {
        max_satir++;

        satir++;
        if(satir>ekran_alt)
        {
            ekran_alt++;
            ekran_ust++;
        }

        int gecici=sutun;

        sutun=0;
        if(gecici==sutun)
        {
            ptr[boyut]=root;
            boyut++;
        }


        printf("%c",root->data);
    }

    node *temp=root;
    root->next=(node*)malloc(sizeof(node));
    root=root->next;
    root->next=NULL;
    root->prev=temp;
}

void yazi()
{
    node *head;
    int sayi=0;
    head=ptr[max_satir];
    while(head!=NULL)
    {
        sayi++;
        head=head->next;
    }


    if(ptr[0]!=NULL&&((satir==0&&sutun==0)||satir!=max_satir||(satir==max_satir&&sutun+1!=sayi&&ptr[satir]!=NULL)))
    {
        ekleme=root;
        root->prev->next=NULL;
        root=root->prev;
        karakter_ekle();
    }
    else
    {
        if(sutun==0)
        {
            ptr[boyut]=root;
            boyut++;

        }
        printf("%c",root->data);
        sutun++;
        if(sutun==70)
        {
            printf("\n");
            max_satir++;
            node * yeni=malloc(sizeof(node));
            yeni->data=10;
            root->next=yeni;
            yeni->prev=root;
            root=yeni;
            yeni->next=NULL;
            sutun=0;
            satir++;

        }
        if(satir>ekran_alt)
        {
            ekran_alt++;
            ekran_ust++;
        }






    }
    node *temp;
    temp=root;

    root->next=(node*)malloc(sizeof(node));
    root=root->next;
    root->next=NULL;
    root->prev=temp;
}

void yontuslari(int x)
{

    int a;

    if(root->data==224)
        a=_getch();
    else
        a=x;

    node *head;
    if(a==72)
    {
        if(satir>=1)
        {


            int sayi1=0,sayi2=0;

            head=ptr[satir];

            if(ptr[satir]==NULL)
            {
                sutun=0;

            }

            else if(satir==max_satir && ptr[satir]!=NULL)
            {

                while(head!=root)
                {
                    sayi1++;
                    head=head->next;

                }

            }

            else
            {

                while(head->data!=10 && satir!=max_satir)
                {
                    sayi1++;
                    head=head->next;
                }

            }
            satir--;
            if(satir<ekran_ust)
            {
                ekran_alt--;
                ekran_ust--;
            }
            head=ptr[satir];

            while(head->data!=10)
            {
                sayi2++;
                head=head->next;
            }


            if(sayi2<sayi1 && sutun>=sayi2)
            {
                sutun=sayi2;

                gotoxy(sutun,satir);
            }
            else
            {
                gotoxy(sutun,satir);

            }
        }

    }

    else if(a==80)
    {

        if(max_satir>satir)
        {
            int sayi1=0,sayi2=0;

            head=ptr[satir];

            while(head->data!=10)
            {
                sayi1++;
                head=head->next;
            }

            satir++;
            if(satir>ekran_alt)
            {
                ekran_alt++;
                ekran_ust++;
            }

            head=ptr[satir];
            if(ptr[satir]==NULL)
            {
                sutun=0;
            }
            else if(satir!=max_satir)
            {

                while(head->data!=10 )
                {
                    sayi2++;
                    head=head->next;
                }
            }
            else if(satir==max_satir && ptr[satir]!=NULL)
            {
                while(head->next!=NULL )
                {
                    sayi2++;
                    head=head->next;
                }
            }



            if(sayi1>sayi2 && sutun>sayi2)
            {
                sutun=sayi2;
            }
            gotoxy(sutun,satir);
        }

    }

    else if(a==75)
    {
        if(sutun>=1)
        {
            sutun--;
            gotoxy(sutun,satir);

        }
        else if(sutun==0)
        {



            if(satir!=0)
            {

                int sayac=0;

                satir--;
                if(satir<ekran_ust)
                {
                    ekran_alt--;
                    ekran_ust--;
                }

                head=ptr[satir];
                while(head->data!=10)
                {
                    sayac++;
                    head=head->next;

                }

                if(sayac==70)
                    sutun=69;
                else
                    sutun=sayac;
                gotoxy(sutun,satir);



            }
        }

    }
    else if(a==77)
    {
        if(ptr[satir]!=NULL)
        {
            head=ptr[satir];

            int i;

            for(i=0; i<sutun; i++)
            {
                head=head->next;
            }

            if(head!=root)
            {

                if(head->data==10||sutun==69)
                {
                    i++;
                    sutun=0;
                    satir++;
                    if(satir>ekran_alt)
                    {
                        ekran_alt++;
                        ekran_ust++;
                    }
                }

                else
                {
                    sutun++;
                }

                gotoxy(sutun,satir);


            }



        }
    }

}

void karakter_sil()
{

    if(ptr[0]!=NULL)
    {
        node * temp;
        int a,sayi=0,var2=0,bas=0;
        node * head=ptr[satir];
        int i;
        for(i=0;i<sutun;i++)
            head=head->next;

        if(satir==0&&sutun==0)
        {
            if(head->data==10)
            {

                boyut--;
                for(a=satir; a<=max_satir+1; a++)
                {
                    ptr[a]=ptr[a+1];
                }
                max_satir--;
            }


            node *say=ptr[satir];
            while(say!=NULL&&say!=root&&say->data!=10)
            {
                sayi++;
                say=say->next;

            }
            if(sayi==70)
                {var2=1;
                }

             head->next->prev=NULL;
            if(head->next!=root)
                ptr[0]=head->next;
            else if(head->next==root)
            {
                ptr[0]=NULL;
                if(head->data!=10) boyut--;
            }


        }
        else if(satir!=0&&sutun==0)
        {
            int x;
            if(ptr[satir]==NULL)
            {
                node * temp;

                if(root->prev->prev!=NULL)temp=root->prev->prev;

                if(satir>=1&&root->prev==ptr[satir-1]&&root->prev->data==10)
                   {
                   boyut--;
                ptr[satir-1]=NULL;
                }
               if(root->prev->prev!=NULL){ temp->next=root;
                root->prev=temp;}
                 else
                    root->prev=NULL;


                max_satir--;

            }

            else if(head==root)
            {
                head->prev=head->prev->prev;
                head->prev->next=root;

                max_satir--;

            }
            else
            {
            temp=ptr[satir];
            sayi=0;
            while(temp!=root&&temp->data!=10)
            {
                sayi++;
                temp=temp->next;
            }
            x=sayi;
            if(sayi==70)
                {var2=1;
                }

                if(head->data==10)
                   {
                   if(ptr[satir+1]!=NULL)boyut--;
                   max_satir--;
                   }
                head->next->prev=head->prev;
                head->prev->next=head->next;
                if(head->next!=root)
                {
                ptr[satir]=head->next;
                }
                else
                {

                    ptr[satir]=NULL;
                    boyut--;
                }
            }
            if(ptr[satir]==NULL||head->data==10){
            satir--;
            if(satir<ekran_ust)
            {
                ekran_alt--;
                ekran_ust--;
            }



            if(ptr[satir+1]!=NULL&&head->data==10)
            {
                for(a=satir+1; a<=max_satir+1; a++)
                {
                    ptr[a]=ptr[a+1];
                }
            }

            temp=ptr[satir];
            sayi=0;
            while(temp!=NULL&&temp!=root&&temp->data!=10)
            {
                sayi++;
                temp=temp->next;
            }
            if(sayi==70||(temp==NULL&&sayi==71))
                sutun=69;
            else
                sutun=sayi;
             }
            sayi=x;




        }
        else
        {

            int var=0;
            if(head->data==10)
                var=1;


            if(head==root)
            {
                if(head->prev->prev!=NULL)head->prev->prev->next=root;
                else
                {
                    ptr[0]=NULL;
                    boyut--;
                }
                head->prev=head->prev->prev;
                sutun--;

            }
            else
            {

                node *say=ptr[satir];
                while(say!=NULL&&say!=root&&say->data!=10)

                {
                    sayi++;
                    say=say->next;

                }
                if(sayi==70)
             {var2=1;
            }

                head->prev->next=head->next;
                head->next->prev=head->prev;
                if(head->data!=10)
                    sutun--;
            }

            if(var==1)
            {
                node *x;
                int k=1,i;
                sayi=0;
                node * say=ptr[satir+k];
                while(say!=NULL&&say->data!=10)
                {
                    sayi++;
                    say=say->next;
                }
                if(say==NULL&&sayi!=0)
                {
                    sayi--;
                }


                int fark=70-sutun;
                while(sayi==70)
                {
                    sayi=0;

                    x=ptr[satir+k];
                    for(i=0; i<fark; i++)
                    {
                        x=x->next;
                    }


                   if(k!=1)
                   {
                       node * tempr=ptr[satir+k]->prev->prev;
                       tempr->next=ptr[satir+k];
                       ptr[satir+k]->prev=tempr;


                   }


                    ptr[satir+k]=x;
                    node * yeni=malloc(sizeof(node));
                    yeni->data=10;
                    x->prev->next=yeni;
                    yeni->prev=x->prev;
                    yeni->next=x;
                    x->prev=yeni;
                    k++;


                    say=ptr[satir+k];
                    while(say!=NULL&&say->data!=10)
                    {
                        sayi++;
                        say=say->next;
                    }
                    if(say==NULL&&sayi!=0)
                    {
                        sayi--;
                    }




                }




                if(sayi>fark)
                {

                    node * tempr=ptr[satir+k]->prev->prev;
                    tempr->next=ptr[satir+k];
                    ptr[satir+k]->prev=tempr;

                    x=ptr[satir+k];
                    for(i=0; i<fark; i++)
                    {
                        x=x->next;
                    }
                    ptr[satir+k]=x;
                    node * yeni=malloc(sizeof(node));
                    yeni->data=10;
                    x->prev->next=yeni;
                    yeni->prev=x->prev;
                    yeni->next=x;
                    x->prev=yeni;

                }
                else
                {


                     if(sayi==0&&ptr[satir+k]!=NULL&&ptr[satir+k]->data==10){


                         if(k!=1){ say->prev->next=say->next;
                          say->next->prev=say->prev;
                         }
                         max_satir--;
                            boyut--;

                            for(i=satir+k;i<=max_satir;i++)
                                 ptr[i]=ptr[i+1];

                     }
                     else if(ptr[satir+k]==NULL)
                     {
                         max_satir--;
                          if(k!=1){

                            root->prev->prev->next=root;
                          root->prev=root->prev->prev;

                         }


                     }

                  else{
                   if(k!=1){ node * tempr=ptr[satir+k]->prev->prev;
                    tempr->next=ptr[satir+k];
                    ptr[satir+k]->prev=tempr;
                   }


                    if(say==NULL)
                    {
                        if(sayi==fark){node * yeni=malloc(sizeof(node));
                        yeni->data=10;
                        root->prev->next=yeni;
                        yeni->prev=root->prev;
                        root->prev=yeni;
                        yeni->next=root;

                          }
                       else{
                        max_satir--;

                       }
                       boyut--;
                        ptr[satir+k]=NULL;

                    }
                    else if(say->data==10)
                    {

                    boyut--;
                        for(a=satir+k;a<=max_satir; a++)
                    {
                        ptr[a]=ptr[a+1];
                    }
                    max_satir--;
                    }
                     }

                }
            }


            var=0;

        }


        if(var2==1)
        {

            node * x;
            node * y;
            int k=1;
            node * say;
            int tam=1,yap=0;
            while(1)
            {
                sayi=0;
                say=ptr[satir+k];
                while(say!=NULL&&say!=root&&say->data!=10)
                {
                    sayi++;
                    say=say->next;
                }

                if((say==NULL&&sayi==0)||((say==root||say->data==10)&&sayi<=1))
                     {
                      yap=1;
                      break;
                     }

                 y=ptr[satir+k]->next;
                 x=ptr[satir+k]->prev->prev;
                 ptr[satir+k]->prev=x;
                 ptr[satir+k]->next=x->next;
                 x->next=ptr[satir+k];
                 ptr[satir+k]->next->next=y;
                 ptr[satir+k]=y;
                 y->prev=x->next->next;
                 y->prev->prev=x->next;
                  k++;

                if(sayi!=70)
                 {tam=0;
                 break;
                 }

            }

            if(tam==1&&yap==1)
            {

                if(say==NULL&&sayi==0)
                {
                    node * sil=root->prev;
                    root->prev->prev->next=root;
                    root->prev=root->prev->prev;
                    free(sil);
                    max_satir--;

                }
                else if(sayi==1)
                    {
                            node * yedek=ptr[satir+k]->prev->prev;
                            yedek->next->next=ptr[satir+k]->next;
                            ptr[satir+k]->next->prev=yedek->next;
                            ptr[satir+k]->next=yedek->next;
                            yedek->next->prev=ptr[satir+k];
                            yedek->next=ptr[satir+k];
                            ptr[satir+k]->prev=yedek;


                        if(say==root)
                        {

                            ptr[satir+k]=NULL;
                            boyut--;
                        }
                        else if(say->data==10)
                        {
                            ptr[satir+k]=yedek->next->next->next;

                        }
                    }
            }
        }
        if(kesyaz==0){
        system("cls");
        node * kontrol=head;
        head=ptr[0];
        while(ptr[0]!=NULL&&head->next!=NULL)
        {
            printf("%c",head->data);
            head=head->next;

        }
        if(sutun==0&&kontrol!=NULL&&kontrol->data==10)
            gotoxy(0,ekran_ust);
        gotoxy(sutun,satir);
        }

    }





}

void karakter_ekle()
{
    node * temp=ptr[satir];
    node * head=ptr[satir];
    int sayi=0;
    int i=0;
    for(i=0; i<sutun; i++)
        head=head->next;



    while(temp!=NULL&&temp->data!=10)
    {
        sayi++;
        temp=temp->next;


    }





    if(satir==0&&sutun==0)
    {
        ekleme->next=ptr[0];
        ptr[0]=ekleme;
        ekleme->prev=NULL;
        ekleme->next->prev=ekleme;
    }
    else if(satir!=0&&sutun==0)
    {

        ekleme->next=ptr[satir];
        ptr[satir]->prev->next=ekleme;
        ekleme->prev=ptr[satir]->prev;
        ekleme->next->prev=ekleme;
        ptr[satir]=ekleme;

    }
    else
    {


        ekleme->next=head;
        ekleme->prev=head->prev;
        head->prev->next=ekleme;
        head->prev=ekleme;

    }


    if(ekleme->data==10)
    {

        int i;
        node * kaydir=head;
        if(ptr[max_satir]==NULL)
            i=max_satir;
        else
            i=max_satir+1;

        for(; i>satir+1; i--)
        {
            ptr[i]=ptr[i-1];
        }
        ptr[i]=kaydir;
        system("cls");
        head=ptr[0];
        while(head!=NULL)
        {
            printf("%c",head->data);
            head=head->next;
        }
        satir++;
        sutun=0;
        if(satir>ekran_alt)
        {
            ekran_alt++;
            ekran_ust++;
        }
        max_satir++;
        boyut++;
        gotoxy(sutun,satir);



    }
    else
    {

        if(temp==NULL)
        {

            if(sayi==69)
            {

                temp=ptr[satir];
                while(temp->next!=NULL)
                {
                    temp=temp->next;


                }
                node * yeni=malloc(sizeof(node));
                yeni->data=10;
                temp->next=yeni;
                yeni->prev=temp;
                yeni->next=NULL;
                root=yeni;
                node *a;
                a=ptr[satir];
                hidecursor();
                gotoxy(0,satir);

                while(a!=NULL)
                {
                    printf("%c",a->data);
                    a=a->next;


                }
                max_satir++;
                boyut++;
                sutun++;
                showcursor();
                gotoxy(sutun,satir);


            }
            else
            {
                node *a;
                a=ptr[satir];
                hidecursor();
                gotoxy(0,satir);
                while(a!=NULL&&a->data!=10)
                {
                    printf("%c",a->data);
                    a=a->next;


                }
                sutun++;
                showcursor();
                gotoxy(sutun,satir);

            }



        }

        else if(temp->data==10&&sayi==0)
        {
            gotoxy(0,satir);
            printf("%c",ekleme->data);
            printf("\n");
            sutun++;
            gotoxy(sutun,satir);
        }
        else if(sayi!=0&&temp->data==10)
        {
            if(sayi==70)
            {
                node *a;
                int k=0;
                sayi=71;
                hidecursor();
                while(sayi==71)
                {

                    sayi=0;
                    node* cikar=temp->prev;
                    temp->prev=cikar->prev;
                    temp->prev->next=temp;

                    a=ptr[satir+k];
                    gotoxy(0,satir+k);
                    for(i=0; i<70; i++)
                    {
                        printf("%c",a->data);
                        a=a->next;
                    }

                    k++;
                    if(temp->next!=NULL)  temp->next->prev=cikar;
                    ptr[satir+k]=cikar;
                    cikar->prev=temp;
                    cikar->next=temp->next;
                    temp->next=cikar;

                    temp=ptr[satir+k];
                    while(temp!=NULL&&temp->data!=10)
                    {
                        sayi++;
                        temp=temp->next;

                    }


                }

                if(temp==NULL&&sayi==1)
                {
                    root=root->next;

                }
                else if(sayi==70&&temp==NULL)
                {

                    node *yeni=malloc(sizeof(node));
                    yeni->data=10;
                    root->next=yeni;
                    yeni->prev=root;
                    root=root->next;
                    max_satir++;
                    boyut++;



                }


                gotoxy(0,satir+k);
                a=ptr[satir+k];
                while(a!=NULL&&a->data!=10)
                {
                    printf("%c",a->data);
                    a=a->next;
                }
                sutun++;
                if(sutun==70)
                {
                    sutun=0;
                    satir++;
                }
                showcursor();
                gotoxy(sutun,satir);

            }
            else
            {

                node *a;
                a=ptr[satir];
                hidecursor();
                gotoxy(0,satir);
                while(a!=NULL&&a->data!=10)
                {
                    printf("%c",a->data);
                    a=a->next;


                }
                sutun++;
                if(sutun==70)
                {
                    sutun=0;
                    satir++;
                    if(satir>ekran_alt)
                    {
                        ekran_alt++;
                        ekran_ust++;
                    }

                }
                showcursor();
                gotoxy(sutun,satir);

            }

        }




    }


}



