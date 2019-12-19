
# Mocksvr

Directory containing the test files required to run the tests. Replace the tokens as necessary.

# Slack API tester
Sample `curl` commands to invoke the Slack APIs.

```bash
curl -H "Host: slack.com" -H "Authorization: Bearer xoxp-821448956678-818775000324-818797461140-4d175b4e14b948d630f195e51478bb0e" -X POST "http://localhost:80/api/chat.postMessage?channel=win31&as_user=true&text=hello"

curl -H "Host: slack.com" -H "Authorization: Bearer xoxp-821448956678-818775000324-818797461140-4d175b4e14b948d630f195e51478bb0e" -X GET "http://127.0.0.1:80/api/conversations.list"

curl -H "Host: slack.com" -H "Authorization: Bearer xoxp-821448956678-818775000324-818797461140-4d175b4e14b948d630f195e51478bb0e" -X GET "http://127.0.0.1:80/api/conversations.history?channel=CPV9L2VT3"
```