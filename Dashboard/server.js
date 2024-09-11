const express = require('express');
const path = require('path');
const bodyParser = require('body-parser');
const app = express();
const server = require('http').Server(app);
const io = require('socket.io')(server);

const port = 3000; // Adjust the port if necessary
const twilio = require('twilio');

// Replace these variables with your own values from your Twilio account
const accountSid = 'AC93bef971153317a4fbfa292b50e5e968'; //SID
const authToken = 'b2e4eb53593829933b816cd09a09de31';  //YOUR_AUTH_TOKEN
const twilioPhoneNumber = '+12343481517';
const recipientPhoneNumber = '+919721859946'; // Replace with the recipient's phone number

// Create a Twilio client
const client = new twilio(accountSid, authToken);
// Middleware to parse JSON and form data
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

// Serve static files (e.g., HTML, CSS)
app.use(express.static(path.join(__dirname, 'public')));

// Endpoint to receive JSON data from ESP8266

app.post('/data', (req, res) => {
    console.log('Received data from ESP8266:');
    console.log(req.body); // Print the received data
    if(req.body.ldr == 0){
        client.messages
        .create({
            body: 'Malfunction is detected at this location https://maps.app.goo.gl/sMHB1WdknbPNYpV4A', // Message text
            from: twilioPhoneNumber, // Your Twilio phone number
            to: recipientPhoneNumber, // Recipient's phone number
        })
        .then((message) => {
            console.log('Message sent successfully:', message.sid);
        })
        .catch((error) => {
            console.error('Error sending message:', error);
        });
    }
    // Emit the received data through WebSocket
    io.emit('latestData', req.body);

    // Send the received data back to the client-side JavaScript
    res.json(req.body);
});

// Endpoint to handle form submission and login
app.post('/login', (req, res) => {
    const { id, password } = req.body;
    
    // Validate the ID and password (you can add your validation logic here)
    if (id === 'root' && password === 'root') {
        // Redirect to home page upon successful login
        res.redirect('/home');
    } else {
        // Redirect to login failed page if login fails
        res.redirect('/login-failed');
    }
});

// Routes
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'views', 'login.html'));
});

// Endpoint to serve the home HTML file
app.get('/home', (req, res) => {
    res.sendFile(path.join(__dirname, 'views', 'home.html'));
});

// Start the server
server.listen(port, () => {
    console.log(`Server listening at http://localhost:${port}`);
});
