if [[ $(curl -sL "http://$HOST/sd/" | grep 'SH.LOG') == "" ]]; then
  echo "FAILED - GET /sd/ - SH.LOG is not found in output";
else
  echo "OK - GET /sd/"
fi;

if [[ $(curl -sL "http://$HOST/sd/internal/" | grep 'HC') == "" ]]; then
  echo "FAILED - GET /sd/internal/ - HC is not found in internal folder";
else
  echo "OK - GET /sd/internal/"
fi;


if [[ $(curl -sL "http://$HOST/sd/internal/hc/hc.txt" | grep 'OK') == "" ]]; then
  echo "FAILED - GET /sd/internal/hc/hc.txt - hc.txt is either not found or doesnt contain OK";
else
  echo "OK - GET /sd/internal/hc/hc.txt"
fi;