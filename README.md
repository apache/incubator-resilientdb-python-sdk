# nexres_sdk

## installing dependencies
`$ python3 -m venv venv`

`$ source venv/bin/activate`

`$ pip install -r requirements.txt`

## running the driver

examples of using the driver can be seen in [test_driver](/test_driver.py)

the base_url is a dummy url. The commit wont actually work till the connection to nexres is complete. But its interesting to see the intermediary steps of asset creation and transfer.


## TODO
- Setting up linting (using [black](https://github.com/psf/black)) through github hooks
- convert the sdk into a package (for pip install)
- Potentially have a docker setup which fetched the nexres image and runs it locally