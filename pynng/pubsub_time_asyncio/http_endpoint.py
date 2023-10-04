# Copyright (C) 2023 twyleg
import json

from flask import Flask, request
from werkzeug.exceptions import HTTPException


flask_app = app = Flask(__name__)


@flask_app.errorhandler(HTTPException)
def handle_exception(e):
    """Return HTTP error with details in JSON format."""
    response = e.get_response()
    response.data = json.dumps(
        {
            "error_code": e.code,
            "error_name": e.name,
            "error_description": e.description,
        }
    )
    response.content_type = "application/json"
    return response


@flask_app.route("/feedme", methods=["POST"])
def feedme():
    request_data = request.data
    print(request_data.decode())
    return "success!"


def start():
    flask_app.run(host="0.0.0.0", port=5000)


if __name__ == "__main__":
    start()