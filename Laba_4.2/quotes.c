

/*  " /* in comment

   comment comment */

int proc1()
{
  return 0;
}


/*  " /* in comment "

   comment comment */

int proc2()
{
  return 0;
}


/*  \" /* in comment "

   comment comment */


int main()
{
  char a = '\"'; // this is comment1 after quotes
  char b = '"'; // this is comment2 after quotes
  char* def = "definition \" /* this is not comment */ !";
  char* def2 = "definition \' /* and this is not comment */ !";

  printf( "hello // notcomment3 " );


  printf( "hi /* notcomment4*/ " );


  printf( " back quoute \" /* notcomment4*/ hello " );

  printf( " back quoute \" /* inside not comment \" quoting */ hello " );

  /* multiline 
     comment " hello \" world "
  */

  printf("8");
}
