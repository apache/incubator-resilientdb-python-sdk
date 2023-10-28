# HTTP Server Endpoints

## Transactions
Note that key-value pairs committed to ResilientDB through the API store the JSON object as the value. To get the intended value of the pair, simply access the value of the JSON object.

### GET /v1/transactions/getall
Get all values

### GET /v1/transactions/get?id=\<string>
Get value of specific id

### GET /v1/transactions/getrange?min_id=\<string>&max_id=\<string>
Get values based on key range

### POST /v1/transactions/commit
Sets a new value for a key. Note that key-value pairs committed to ResilientDB through the API store the JSON object as the value. To get the intended value of the pair, simply access the value of the JSON object.

Ex: `curl -X POST  -d '{"id":"samplekey","value":"samplevalue"}' localhost:18000/v1/transactions/commit`

## Blocks

### GET /v1/blocks/getall
Retrieve all blocks

### GET /v1/blocks/get?batch_size=\<int>
Retrieve all blocks, grouped in batch sizes of the int parameter

### GET /v1/blocks/getrange?min_seq=\<int>&max_seq=\<int>
Retrieve list of blocks within a range of sequence numbers

## Miscellaneous
### GET /populatetable
Used for the Explorer webpage