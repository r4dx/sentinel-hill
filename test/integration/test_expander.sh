if [ `curl -X POST -sL -w "%{http_code}" "http://$HOST/gpio-expander/0" -o /dev/null` != "200" ]; then
  echo "FAILED - POST /gpio-expander/0";
else
  echo "OK - POST /gpio-expander/0"
fi;

if [ `curl -X POST -sL -w "%{http_code}" "http://$HOST/gpio-expander/8" -o /dev/null` != "200" ]; then
  echo "FAILED - POST /gpio-expander/8";
else
  echo "OK - POST /gpio-expander/8"
fi;

if [ `curl -X POST -sL -w "%{http_code}" "http://$HOST/gpio-expander/17" -o /dev/null` != "404" ]; then
  echo "FAILED - POST /gpio-expander/16 - result is not 404";
else
  echo "OK - POST /gpio-expander/16"
fi;


if [ `curl -X POST -sL -w "%{http_code}" "http://$HOST/gpio-expander/" -o /dev/null` != "200" ]; then
  echo "FAILED - POST /gpio-expander/";
else
  echo "OK - POST /gpio-expander/"
fi;