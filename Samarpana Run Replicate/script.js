// Live Date and Time
function updateDateTime() {
  const now = new Date();
  document.getElementById("datetime").innerText =
    now.toLocaleString();
}
setInterval(updateDateTime, 1000);
updateDateTime();

// Form Validation
document.getElementById("registrationForm").addEventListener("submit", function(e) {
  e.preventDefault();

  const fields = ["fullName", "email", "mobile", "dob", "university", "usn", "tshirt"];
  for (let id of fields) {
    if (!document.getElementById(id).value.trim()) {
      alert("Please fill the required field: " + id);
      return;
    }
  }

  const mobile = document.getElementById("mobile").value;
  if (!/^\d{10}$/.test(mobile)) {
    alert("Please enter a valid 10-digit mobile number.");
    return;
  }

  const pincode = document.getElementById("pincode").value;
  if (pincode && !/^\d{6}$/.test(pincode)) {
    alert("Please enter a valid 6-digit pincode.");
    return;
  }

  if (!document.getElementById("confirm").checked) {
    alert("You must confirm the terms to proceed.");
    return;
  }

  alert("Registration Successful! 🎉");
  this.reset();
});
