/*  weather.c  ...
 *
 * Copyright (c) ...
 *
 * Project name:    CS50 Lab assignment 3
 * Component name:  weather
 *
 * Usage:       
 *
 * Results:
 *
 * Date Created:    April 2014
 *
 * Special considerations:
 *  Links with mycurl.c and libcurl.a
 */

/* system includes go here */

/* project includes go here */
#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
#include<ctype.h>
#include<curl/curl.h>
#include "mycurl.h"

/* ... */

 void parse(struct curlResponse *s, char tag_string[]){
  char *p, *token;
  char delim1[] = ">";
  char string[50];
  char delim2[] = "<";
  //create the search string
  sprintf(string, "<%s>", tag_string);
  //find the line containing the search string
  p = strstr(s->ptr, string);
  //If the string was found then crop out info between the tags
  if( p!= NULL){
    token = strtok(p, delim1);
    token = strtok(NULL, delim1);
    token = strtok(token, delim2);
    //print info to stdout
    fprintf(stdout, " %s: %s\n",tag_string, token);
  }
}

int main(int argc, char **argv)
{
    /* local variables */
 char URL[100];
 char check[6];
 char temp[100];
 int i;

    /* curl stuff */
 CURL *curl;
 CURLcode res;
 struct curlResponse s;

    /* check args */
 if(argc == 1){
   fprintf(stderr, "Invalid Argument: User must enter a single 4 letter Station Code\n");
   return 1;
 }

//convert to all upercase letters
 for(i=0; i<sizeof argv[1]; i++)
   temp[i] = toupper(argv[1][i]);


    /* allocate and intiialize the output area */
 init_curlResponse(&s);

    /* create the URL from the format string */
    /* ... */
 sprintf(URL, "http://w1.weather.gov/xml/current_obs/%s.xml", temp);

    /* initialize curl */
 curl = curl_easy_init();

 if(curl) {
        /* set the URL we want to visit */
  curl_easy_setopt(curl, CURLOPT_URL, URL);
        /* set the function curl should call with the result */
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        /* set the buffer into which curl should place the data */
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

        /* Perform the request, res will get the return code */
  res = curl_easy_perform(curl);
        /* make sure it worked */
  if ((int)res != 0){
   fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
   return 1;
 }
        /* check: if the weather station code wasn't found, we get back HTML instead of XML  */
 for(i=0; i<(sizeof check); i++){
   check[i] = *(s.ptr+i);
 }
 if(strncmp(check, "<!DOC", 2) == 0){
   fprintf(stderr, "Error: Invalid Station Code\n");
   return 1;
 }
 else{
        	/* otherwise, select the desired output from the results */
  parse(&s, "visibility_mi");
  parse(&s, "wind_string");
  parse(&s, "relative_humidity");
  parse(&s, "temperature_string");
  parse(&s, "weather");
  parse(&s, "observation_time");
  parse(&s, "station_id");
  parse(&s, "location");
  parse(&s, "credit");

  /* always cleanup */
  curl_easy_cleanup(curl);
}
}
return 0;
}
