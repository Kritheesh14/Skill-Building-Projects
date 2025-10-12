// --- Geolocation API ---
const locationDiv = document.getElementById('location');
const getLocationBtn = document.getElementById('getLocationBtn');

getLocationBtn.addEventListener('click', () => {
    if (navigator.geolocation) {
        locationDiv.textContent = 'Fetching location...';
        navigator.geolocation.getCurrentPosition(showPosition, showError);
    } else {
        locationDiv.textContent = "Geolocation is not supported by this browser.";
    }
});

function showPosition(position) {
    locationDiv.innerHTML = `Latitude: ${position.coords.latitude.toFixed(4)}<br>Longitude: ${position.coords.longitude.toFixed(4)}`;
}

function showError(error) {
    let message = "An unknown error occurred.";
    switch (error.code) {
        case error.PERMISSION_DENIED:
            message = "User denied the request for Geolocation."
            break;
        case error.POSITION_UNAVAILABLE:
            message = "Location information is unavailable."
            break;
        case error.TIMEOUT:
            message = "The request to get user location timed out."
            break;
        case error.UNKNOWN_ERROR:
            message = "An unknown error occurred."
            break;
    }
    locationDiv.textContent = `Error fetching location: ${message}`;
}

// --- Asynchronous Data Simulation ---
const asyncDataDiv = document.getElementById('asyncData');
const fetchDataBtn = document.getElementById('fetchDataBtn');

const fetchData = () => {
    return new Promise((resolve) => {
        setTimeout(() => {
            resolve({ name: "WebTech Demo", message: "Data loaded successfully!" });
        }, 1500); // Simulate network delay
    });
};

const displayData = async () => {
    asyncDataDiv.textContent = 'Fetching data...';
    try {
        const data = await fetchData();
        asyncDataDiv.innerHTML = `<strong>Name:</strong> ${data.name}, <strong>Message:</strong> ${data.message}`;
    } catch (error) {
        asyncDataDiv.textContent = 'Failed to fetch data.';
    }
};

fetchDataBtn.addEventListener('click', displayData);


// --- XML to JSON Conversion ---
const jsonDataPre = document.getElementById('jsonData');
const convertBtn = document.getElementById('convertBtn');

const xmlString = `
    <Student>
        <Name>Kritheesh Shah</Name>
        <Course>Web Tech</Course>
        <University>PESU</University>
    </Student>
`;

const convertXmlToJson = () => {
    const parser = new DOMParser();
    const xmlDoc = parser.parseFromString(xmlString, "text/xml");

    const studentNode = xmlDoc.getElementsByTagName("student")[0];
    const name = studentNode.getElementsByTagName("name")[0].childNodes[0].nodeValue;
    const course = studentNode.getElementsByTagName("course")[0].childNodes[0].nodeValue;
    const university = studentNode.getElementsByTagName("university")[0].childNodes[0].nodeValue;

    const jsonObj = {
        name: name,
        course: course,
        university: university,
    };

    jsonDataPre.textContent = JSON.stringify(jsonObj, null, 2);
};

convertBtn.addEventListener('click', convertXmlToJson);