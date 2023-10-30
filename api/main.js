const express = require("express");
const {SerialPort} = require("serialport");
const {StringStream} = require("scramjet");

const states = ["START", "LOCK", "UNLOCK"];
let state = 1;

function Serial() {
    let connection = null;

    function initialize() {
        const conn = new SerialPort({ path: '/dev/tty.usbmodem1101', baudRate: 9600 }, (error) => {
            if (error) {
                connection = null;

                return;
            }

            connection = conn;

            connection.on("error", () => {
                connection = null;
            });

            connection.pipe(new StringStream())
                .lines("\n")
                .each((value) => {
                    const action = Number(value);

                    if (isNaN(action) || action > 2)
                        return;

                    state = action;
                })
        });
    }

    return {
        start() {
            setInterval(() => {
                if (!connection)
                    initialize();
            }, 1000);
        },
        send(value) {
            const action = Number(value);

            if (isNaN(action) || action > 2 || !connection)
                return;

            connection.write(value);
        },
        available() {
            return !!connection;
        }
    }
}

const serial = Serial();

const app = express();
const port = 3000;

app.use("/", express.static("static"));

app.get("/api/state", (_, res) => {
    const body = {
        state
    };

    const available = serial.available();
    if (!available) {
        state = 0;
    }
    else {
        serial.send("0");
    }

    res.send(body);
});

app.patch("/api/change", (_, res) => {
    const available = serial.available();

    if (!available) {
        res.status(500).send();
        return;
    }

    state = state === 1 ? 2 : state === 2 ? 1 : 0;

    serial.send(state.toString());

    res.status(200).send();
});

app.listen( port, () => {
    console.log("started");

    serial.start();
});
