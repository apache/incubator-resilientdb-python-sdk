# resdb_sdk

## Check Python is up-to-date (3.9+)
`$ python3 --version`

If your Python version number is too low you may encounter type hinting issues when attempting to run the code

## Installing dependencies
`$ python3 -m venv venv`

`$ source venv/bin/activate`

`$ pip install -r requirements.txt`

## Running the driver

examples of using the driver can be seen in [test_driver](/test_driver.py)

replace the db_root_url with the url of resilient db e.g `120.0.0.1:8080`


## TODO
- Setting up linting (using [black](https://github.com/psf/black)) through github hooks
- convert the sdk into a package (for pip install)
- Potentially have a docker setup which fetched the Resdb image and runs it locally
