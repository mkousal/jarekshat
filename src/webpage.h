const char index_html[] PROGMEM =
"<html data-ember-extension=\"1\">\n"
"  <head>\n"
"    <meta charset=\"UTF-8\">\n"
"    <meta name=\"viewport\" content=\"width=device-width\", initial-scale=1.0>\n"
"    \n"
"    <style type=\"text/css\">\n"
"    body{\n"
"      background: #3a3747;\n"
"      font-family: Helvetica;\n"
"      -webkit-appearance: none;\n"
"      color: white;\n"
"      text-align: center;\n"
"    }\n"
"    \n"
"    input{\n"
"      width: 85%;\n"
"      border: 0;\n"
"      padding: 10px;\n"
"      border-radius: 15px;\n"
"      font-size: 25px;\n"
"      background: #4591a0;\n"
"      -webkit-appearance: none;\n"
"      color: white;\n"
"      text-align: center;\n"
"    }\n"
"    \n"
"    input:hover{\n"
"      background: #d7790d;\n"
"      color: white;\n"
"    }\n"
"    \n"
"    </style>\n"
"  </head>\n"
"  <body>\n"
"    <h1>Jarkův klobouk do nepohody</h1>\n"
"    \n"
"    <form action=\"\" method=\"GET\" style=\"display:inline\">\n"
"      <input name=\"cmd\" value=\"up\" type=\"hidden\">\n"
"      <input value=\"Přidat jas\" type=\"submit\" style=\"width:42.5%; display:inline\">\n"
"    </form>\n"
"\n"
"    <form action=\"\" method=\"GET\" style=\"display:inline\">\n"
"      <input name=\"cmd\" value=\"down\" type=\"hidden\">\n"
"      <input value=\"Ubrat jas\" type=\"submit\" style=\"width:42.5%; display:inline\">\n"
"    </form> <p>\n"
"\n"
"    <form action=\"\" method=\"GET\">\n"
"      <input name=\"cmd\" value=\"off\" type=\"hidden\">\n"
"      <input value=\"Budiž tma!\" type=\"submit\">\n"
"    </form>\n"
"\n"
"    <form action=\"\" method=\"GET\">\n"
"      <input name=\"cmd\" value=\"find\" type=\"hidden\">\n"
"      <input value=\"Přivolávač kamarádů\" type=\"submit\">\n"
"    </form>\n"
"    \n"
"    <form action=\"\" method=\"GET\">\n"
"      <input name=\"cmd\" value=\"wave\" type=\"hidden\">\n"
"      <input value=\"Chci být duha\" type=\"submit\">\n"
"    </form>\n"
"    \n"
"    <form action=\"\" method=\"GET\">\n"
"      <input name=\"cmd\" value=\"snake\" type=\"hidden\">\n"
"      <input value=\"Jdu si hrát na policajty\" type=\"submit\">\n"
"    </form>\n"
"    \n"
"    <form action=\"\" method=\"GET\">\n"
"      <input name=\"cmd\" value=\"disco\" type=\"hidden\">\n"
"      <input value=\"Uděláme diskošku\" type=\"submit\">\n"
"    </form>\n"
"    \n"
"    <form action=\"\" method=\"GET\">\n"
"      <input name=\"cmd\" value=\"beat\" type=\"hidden\">\n"
"      <input value=\"Moje klidná mysl\" type=\"submit\">\n"
"    </form>\n"
"    \n"
"    <form action=\"\" method=\"GET\">\n"
"      <input name=\"cmd\" value=\"rearon\" type=\"hidden\">\n"
"      <input value=\"Chci vidět na klávesnici\" type=\"submit\">\n"
"    </form>\n"
"\n"
"    <form action=\"\" method=\"GET\">\n"
"      <input name=\"cmd\" value=\"rearoff\" type=\"hidden\">\n"
"      <input value=\"Zhasni nad klávesnicí\" type=\"submit\">\n"
"    </form>\n"
"    \n"
"  </body>\n"
"</html>";