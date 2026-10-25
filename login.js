// Vite passes anything starting with /api along to the backend
const API_URL = "/api";

// Runs when the "Show password" box is clicked
function togglePassword() {
  const passwordBox = document.getElementById("password");

  if (passwordBox.type === "password") {
    passwordBox.type = "text";
  } else {
    passwordBox.type = "password";
  }
}

// Puts a message on the page in red or green
function showMessage(text, color) {
  const message = document.getElementById("message");
  message.textContent = text;
  message.style.color = color;
}

// Runs when the "Sign In" button is clicked
async function login() {
  const email = document.getElementById("email").value;
  const password = document.getElementById("password").value;

  // Make sure both boxes are filled in
  if (email === "" || password === "") {
    showMessage("Please enter your email and password.", "red");
    return;
  }

  try {
    // Send the email and password to the backend
    const response = await fetch(API_URL + "/auth/login", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ email: email, password: password })
    });

    if (response.ok) {
      // Login worked, so save the token for later pages
      const data = await response.json();
      localStorage.setItem("token", data.accessToken);
      localStorage.setItem("role", data.user.role);

      if (data.user.role === "employee") {
        // Employees go to their shift page
        window.location.href = "employee.html";
      } else {
        showMessage("Login successful! You are a " + data.user.role + ".", "green");
      }
    } else if (response.status >= 500) {
      // 500 and up means a server problem (for example, the backend is off)
      showMessage("Could not connect to the server.", "red");
    } else {
      // Wrong email or password
      showMessage("Invalid email or password.", "red");
    }
  } catch (error) {
    // The request could not be sent at all
    showMessage("Could not connect to the server.", "red");
  }
}
