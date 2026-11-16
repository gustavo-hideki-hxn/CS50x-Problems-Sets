# Harvard CS50x - Week 9 - Problem Set 9 
# Birthdays: https://cs50.harvard.edu/x/psets/9/birthdays/
# Base code and template provided by Harvard

import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        if not name or not month or not day:
                print("Some(or all) of inputs is(are) empty")
                return redirect("/")

        try:
            month = int(month)
            day = int(day)
        except ValueError:
                print("Not integer input")
                return redirect ("/")

        if int(month) not in range(1, 13):
            print("Invalid month")
            return redirect("/")

        if int(day) not in range(1, 32):
            print("Invalid day")
            return redirect("/")

        db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)
        return redirect("/")

    else:
        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", birthdays=birthdays)


@app.route("/deregister", methods=["POST"])
def deregister():
    id = request.form.get("id")
    if id:
        db.execute("DELETE FROM birthdays WHERE id = ?", id)
    return redirect("/")
