if [ `curl -X DELETE -sL -w "%{http_code}" "http://$HOST/logs" -o /dev/null` != "200" ]; then
  echo "FAILED - DELETE /logs";
else
  echo "OK - DELETE /logs"
fi;

if [ `curl -sL -w "%{http_code}" "http://$HOST/logs" -o /dev/null` != "200" ]; then
  echo "FAILED - GET /logs";
else
  echo "OK - GET /logs"
fi;