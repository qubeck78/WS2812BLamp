#include "web.h"
#include "lamp.h"

WebServer  web(80);
int        currentScene;

void webIndexHtml()
{
  String webPage;
  String newScene;

  newScene = web.arg("scene");
  if( newScene != NULL )
  {

      if( newScene.toInt() != currentScene )
      {
        currentScene = newScene.toInt();
        lampSetScene( currentScene );
      }
  }
  


  webPage = "<!DOCTYPE html> <html>\n";
  webPage +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  webPage +="<link rel=\"icon\" type=\"image/png\" href=\"data:image/png;base64,iVBORw0KGgo=\">";
  webPage +="<title>Lampa</title>\n";
  webPage +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  webPage +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  webPage +=".button {display: block;width: 120px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  webPage +=".button-on {background-color: #3498db;}\n";
  webPage +=".button-on:active {background-color: #2980b9;}\n";
  webPage +=".button-off {background-color: #34495e;}\n";
  webPage +=".button-off:active {background-color: #2c3e50;}\n";
  webPage +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  webPage +="</style>\n";
  webPage +="</head>\n";
  webPage +="<body>\n";
  webPage +="<h1>Lampa lazienka</h1>\n";
  webPage +="<h3>Wybierz scene:</h3>\n"; 

  if( currentScene == 0 )
  {
    webPage +="<a class=\"button button-on\" href=\"/?scene=0\">Wylacz</a>\n";     
  }
  else
  {
    webPage +="<a class=\"button button-off\" href=\"/?scene=0\">Wylacz</a>\n"; 
  }
  
  if( currentScene == 1 )
  {
    webPage +="<a class=\"button button-on\" href=\"/?scene=1\">Bialy</a>\n"; 
  }
  else
  {
    webPage +="<a class=\"button button-off\" href=\"/?scene=1\">Bialy</a>\n";     
  }
  
  if( currentScene == 2 )
  {
    webPage +="<a class=\"button button-on\" href=\"/?scene=2\">Szum bialy</a>\n"; 
  }
  else
  {
    webPage +="<a class=\"button button-off\" href=\"/?scene=2\">Szum bialy</a>\n";     
  }
  
  if( currentScene == 3 )
  {
    webPage +="<a class=\"button button-on\" href=\"/?scene=3\">Szum kolorowy</a>\n"; 
  }
  else
  {
    webPage +="<a class=\"button button-off\" href=\"/?scene=3\">Szum kolorowy</a>\n";     
  }

  if( currentScene == 4 )
  {
    webPage +="<a class=\"button button-on\" href=\"/?scene=4\">Ogien</a>\n"; 
  }
  else
  {
    webPage +="<a class=\"button button-off\" href=\"/?scene=4\">Ogien</a>\n";     
  }
  
  if( currentScene == 5 )
  {
    webPage +="<a class=\"button button-on\" href=\"/?scene=5\">Prostakaty kolorowe</a>\n"; 
  }
  else
  {
    webPage +="<a class=\"button button-off\" href=\"/?scene=5\">Prostakaty kolorowe</a>\n";     
  }
  if( currentScene == 6 )
  {
    webPage +="<a class=\"button button-on\" href=\"/?scene=6\">Oddech bialy</a>\n"; 
  }
  else
  {
    webPage +="<a class=\"button button-off\" href=\"/?scene=6\">Oddech bialy</a>\n";     
  }
  webPage +="</body>\n";
  webPage +="</html>\n";
  
  web.send( 200, "text/html", webPage );
  
}


int webInit()
{
  web.on( "/", webIndexHtml );
  web.begin();

  currentScene = 1;
  
}

int webMain()
{
  web.handleClient();
  return 0;
}
