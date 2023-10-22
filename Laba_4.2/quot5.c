
void function(int a, int b)
{
  const char* quot1 = "Line \" with /* not comment \
and string cut";

  /* Comment "quot" inside  
    */

  printf("1");

  /* Comment "qu \" ot" inside  
    */

  printf("2");
    
  /* Comment "qu 
           ot" inside  
    */

  printf("3");

  /* Comment "qu 
       \"    ot" inside  
    */

  printf("4");

  printf("str");
}
