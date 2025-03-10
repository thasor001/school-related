const name_err = document.getElementById("name");
const email_err = document.getElementById("email");
const password_err = document.getElementById("password");
const confirm_err = document.getElementById("confirm");

const name = document.getElementById("name_input");
const email = document.getElementById("email_input");
const password = document.getElementById("password_input");
const confirm = document.getElementById("confirm_input");

function check() {
	let passed = true;

	if (name.value === "") { name_err.style.display = "flex"; passed = false; }
	else { name_err.style.display = "none"; }

	if (email.value === "") { email_err.style.display = "flex"; passsed = false; }
	else { email_err.style.display = "none"; }

	if (password.value === "") { password_err.style.display = "flex"; passed = false; }
	else { password_err.style.display = "none"; }

	if (confirm.value === password.value) { confirm_err.style.display = "none"; }
	else { confirm_err.style.display = "flex"; passed = false; }

	if (passed) { console.log("logged in as : ", name.value); }
}
