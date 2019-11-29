#include <Arduino.h>

extern const String navbar = "\
<nav class=\"navbar navbar-expand-lg navbar-light bg-light\"> \
  <a class=\"navbar-brand\" href=\"/\"> Home </a> \
  <button class=\"navbar-toggler\" type=\"button\" data-toggle=\"collapse\" data-target=\"#navbarSupportedContent\" aria-controls=\"navbarSupportedContent\" aria-expanded=\"false\" aria-label=\"Toggle navigation\"> \
    <span class=\"navbar-toggler-icon\"></span> \
  </button> \
  <div class=\"collapse navbar-collapse\" id=\"navbarSupportedContent\"> \
    <ul class=\"navbar-nav mr-auto\"> \
      <li class=\"nav-item active\"> \
        <a class=\"nav-link\" href = \"/settings\"> Settings <span class=\"sr-only\">(current)</span></a> \
      </li> \
      <li class=\"nav-item active\"> \
        <a class=\"nav-link\" href = \"/debug\"> Debug <span class=\"sr-only\">(current)</span></a> \
      </li> \
    </ul> \
  </div> \
</nav> \
";

extern const String main_template = "\
<!DOCTYPE html> \
<html lang=\"en\"> \
  <head> \
    {refresh} \
    <meta charset=\"utf-8\"> \
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\"> \
    <link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css\" integrity=\"sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T\" crossorigin=\"anonymous\"> \
    <title> Solar Panel Control </title> \
    {navbar} \
  </head> \
  {body} \
  <script src=\"https://code.jquery.com/jquery-3.2.1.slim.min.js\" integrity=\"sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN\" crossorigin=\"anonymous\"></script> \
  <script src=\"https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js\" integrity=\"sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q\" crossorigin=\"anonymous\"></script> \
  <script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js\" integrity=\"sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl\" crossorigin=\"anonymous\"></script> \
</html> \
";

extern const String homepage_body = "\
  <body> \
    <div class=\"container\"> \
      <div class=\"row\"> \
        <div class=\"col\"> \
          <form action=\"/\" method=\"POST\"> \
            <input type=\"hidden\" name=\"left-att\" value=\"left\"> \
            <input class=\"btn btn-primary btn-md\" type=\"submit\" value=\"motor_left\"> \
          </form> \
        </div> \
        <div class=\"col\"> \
          <form action=\"/\" method=\"POST\"> \
            <input type=\"hidden\" name=\"right-att\" value=\"right\"> \
            <input class=\"btn btn-primary btn-md\" type=\"submit\" value=\"motor_right\"> \
          </form> \
        </div> \
        <div class=\"col\"> \
          <form action=\"/\" method=\"POST\"> \
            <input type=\"hidden\" name=\"auto-att\" value=\"auto\"> \
            <input class=\"btn btn-info btn-md\" type=\"submit\" value=\"motor_auto\"> \
          </form> \
        </div> \
        <div class=\"col\"> \
          <form action=\"/\" method=\"POST\"> \
            <input type=\"hidden\" name=\"stop-att\" value=\"stop\"> \
            <input class=\"btn btn-danger btn-md\" type=\"submit\" value=\"motor_stop\"> \
          </form> \
        </div> \
      </div> \
      <br> \
      <div class=\"row\"> \
        {motor_status} \
      </div> \
    </div> \
  </body> \
";

extern const String notification = "\
<nav aria-label=\"breadcrumb\"> \
  <ol class=\"breadcrumb\"> \
    <li class=\"breadcrumb-item active\" aria-current=\"page\"> {note} </li> \
  </ol> \
</nav> \
";

extern const String settings_body = "\
<body> \
  <div class=\"container\"> \
    <div class=\"row\"> \
      <p> This value changes the resolution received from the solar sensors acceptible values are from 1 - 64.</p> \
    </div> \
    <br> \
    <div class=\"row\"> \
      <div class=\"col\"> \
        <form class=\"form-inline\" action=\"/settings\" method=\"POST\"> \
          <input class=\"form-control\" type=\"number\" name=\"resoultion\" value=\"1\"> \
          <input class=\"btn btn-primary btn-md\" type=\"submit\" value=\"Edit\"> \
        </form> \
      </div> \
      <div class=\"col\"> \
        {res_num} \
      </div> \
    </div> \
    <div class=\"row\"> \
      <p> This value changes the number of minutes for the auto motor activation. </p> \
    </div> \
    <br> \
    <div class=\"row\"> \
      <div class=\"col\"> \
        <form class=\"form-inline\" action=\"/settings\" method=\"POST\"> \
          <input class=\"form-control\" type=\"number\" step=\"0.1\" name=\"minutes\" value=\"10\"> \
          <input class=\"btn btn-primary btn-md\" type=\"submit\" value=\"Edit\"> \
        </form> \
      </div> \
      <div class=\"col\"> \
        {min_num} \
      </div> \
    </div> \
    <div class=\"row\"> \
      <p> This value changes the cutoff point for the auto motor function Remeber! it correlates with the resoultion. </p> \
    </div> \
    <br> \
    <div class=\"row\"> \
      <div class=\"col\"> \
        <form class=\"form-inline\" action=\"/settings\" method=\"POST\"> \
          <input class=\"form-control\" type=\"number\" name=\"cutoff\" value=\"100\"> \
          <input class=\"btn btn-primary btn-md\" type=\"submit\" value=\"Edit\"> \
        </form> \
      </div> \
      <div class=\"col\"> \
        {cutoff_num} \
      </div> \
    </div> \
  </div> \
</body> \
";
extern const String debug_body = "\
<body> \
  <div class=\"container\"> \
    <div class=\"row\"> \
      {sensor_1} \
    </div> \
    <div class=\"row\"> \
      {sensor_2} \
    </div> \
  </div> \
</body> \
";

//Global Values
extern String setting = "Motor on auto mode.";
extern int resolution = 1;
extern float minutes = 10.0f;
extern int cutoff = 100;
