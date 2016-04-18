/****************************************
  Demonstrates how to update a Google Spreadsheet from your 
  TI LaunchPad using Temboo and the Google Spreadsheets API.  
   
  Learn to auto-generate your own code for the TI LaunchPad
  with Temboo's Getting Started examples and tutorials.
 
  ** http://temboo.com/hardware/ti **
 
*****************************************/
 
/* 
  Set up Instructions:
 
  1. Create a Temboo account: http://www.temboo.com

  2. Retrieve your Temboo application details: http://www.temboo.com/account/applications

  3. Replace the values in the TembooAccount.h tab with your Temboo application details

  4. You'll also need a Google Spreadsheet that includes a title in the first row 
     of each column that data will be written to. This example saves values to three columns:
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
  How to Write to spreadsheet in main:
  
  In the main file in this project make sure that initWiFi(); is called in the setup() function.
 
  When you want to write to your spreadsheet simply call add_line_to_sheet(ROW_DATA); 
  ROW_DATA is a string that contains a list of items separated by commas. Each item will be placed in 
  the coresponding column in the spreadsheet (the first row of ever column must be filled in with a column header). 
*/




#include <SPI.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <Temboo.h>
#include "TembooAccount.h" // contains Temboo account information
                           // as described in the footer comment below


/*** SUBSTITUTE YOUR VALUES BELOW: ***/

// note that for additional security and reusability, you could
// use #define statements to specify these values in a .h file.

// the clientID found in Google's Developer Console under APIs & Auth > Credentials
const String CLIENT_ID = "";

// the clientSecret found in Google's Developer Console under APIs & Auth > Credentials
const String CLIENT_SECRET = "";

// returned after running FinalizeOAuth
const String REFRESH_TOKEN = "";

// the name of the spreadsheet in your Google Docs/Drive
// that you you want to send data to
const String SPREADSHEET_TITLE = "";



WiFiClient client;


void initWiFi()
{
    Serial.begin(9600);

  int wifiStatus = WL_IDLE_STATUS;

  // determine if the WiFi Shield is present.
  Serial.print("\n\nShield:");
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("FAIL");
    
    // if there's no WiFi shield, stop here.
    while(true);
  }
 
  while(wifiStatus != WL_CONNECTED) {
    Serial.print("WiFi:");
    wifiStatus = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    if (wifiStatus == WL_CONNECTED) {
      Serial.println("OK");
    } else {
      Serial.println("FAIL");
    }
    delay(5000);
  }
}

void add_line_to_sheet(String ROW_DATA)
{    
    Serial.println("Appending value to spreadsheet...");

    // we need a Process object to send a Choreo request to Temboo
    TembooChoreo AppendRowChoreo(client);

    // invoke the Temboo client
    // NOTE that the client must be reinvoked and repopulated with
    // appropriate arguments each time its run() method is called.
    AppendRowChoreo.begin();

    // set Temboo account credentials
    AppendRowChoreo.setAccountName(TEMBOO_ACCOUNT);
    AppendRowChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    AppendRowChoreo.setAppKey(TEMBOO_APP_KEY);

    // identify the Temboo Library choreo to run (Google > Spreadsheets > AppendRow)
    AppendRowChoreo.setChoreo("/Library/Google/Spreadsheets/AppendRow");

    // your Google application client ID
    AppendRowChoreo.addInput("ClientID", CLIENT_ID);
    // your Google application client secert
    AppendRowChoreo.addInput("ClientSecret", CLIENT_SECRET);
    // your Google OAuth refresh token
    AppendRowChoreo.addInput("RefreshToken", REFRESH_TOKEN);
    // the data you want to append to the spreadsheet
    AppendRowChoreo.addInput("RowData", ROW_DATA);
    // the title of the spreadsheet you want to append to
    AppendRowChoreo.addInput("SpreadsheetTitle", SPREADSHEET_TITLE);

    // run the Choreo and wait for the results
    // the return code (returnCode) will indicate success or failure 
    unsigned int returnCode = AppendRowChoreo.run();

    // a return code of zero (0) means everything worked
    if (returnCode == 0) {
      Serial.println("Success! Spreadsheet updated!\n");
    } 
    else {
      // a non-zero return code means there was an error
      // read and print the error message
      while (AppendRowChoreo.available()) {
        char c = AppendRowChoreo.read();
        Serial.print(c);
      }
    }

    AppendRowChoreo.close();
    delay(30000);
}



