/*
  Hardware Needed:
  
  For this system you MUST be use the following:
    Launchpad MSP-430
    CC3100 WiFi BoosterPack
  
*/

 
/* 
  Set up Instructions:
 
  1. Create a Temboo account: http://www.temboo.com

  2. Retrieve your Temboo application details: http://www.temboo.com/account/applications

  3. Replace the values in the TembooAccount.h tab with your Temboo application details
    The #define WIFI_SSID "" and #define WIFI_PASSWORD "" referes to the wireless network you will 
    be using. The campus internet systems like illinois.net and illinois_start.net do NOT work. 
    
  4. You'll also need a Google Spreadsheet that includes a title in the first row 
     of each column that data will be written to. You can make the columns refere to anything
     you like. the following is just an example.
     This example saves values to three columns:
     company, location, and contact. The spreadsheet should be set up with three column names:
  
       Company | Location | Contact   
     +---------+----------+---------+
               |          |        
 
  5. Google Spreadsheets requires you to authenticate via OAuth. Follow the steps
     in the link below to find your ClientID, ClientSecret, and RefreshToken, and then 
     use those values to overwrite the placeholders in the code below. 
     
     https://temboo.com/library/Library/Google/OAuth/
     
     For the scope field, you need to use: https://spreadsheets.google.com/feeds/
     
     Here's a video outlines how Temboo helps with the OAuth process: 
     
     https://www.temboo.com/videos#oauthchoreos
     
     And here's a more in-depth version of this example on our website: 
     
     https://temboo.com/hardware/ti/update-google-spreadsheet
 
  6. Next, upload the sketch to your LaunchPad and open Energia's serial monitor
 
     Note: you can test this Choreo and find the latest instructions on our website:
     https://temboo.com/library/Library/Google/Spreadsheets/AppendRow/
 
     This example code is in the public domain.
*/

/*
  How to Write to spreadsheet from the main function:
  
  In the main file in this project make sure that initWiFi(); is called in the setup() function.
 
  When you want to write to your spreadsheet simply call add_line_to_sheet(ROW_DATA); 
  ROW_DATA is a string that contains a list of items separated by commas. Each item will be placed in 
  the corresponding column in the spreadsheet (the first row of ever column must be filled in with a column header). 

  for example, if ROW_DATA = "first, blue, 3"
  then the cell int the first column would read "first"
  the second column would read "blue"
  the third column would read "3"
  
 
 IMPORTANT NOTE:
   When calling  add_line_to_sheet(ROW_DATA);  RPW_DATA must be a string variable you cannot 
    call  add_line_to_sheet(); with string provieded in quotes like the following add_line_to_sheet("StringValue");  
   the string value must be supplied through a variable  
 */


