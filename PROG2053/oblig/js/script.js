// JAVASCRIPT for task b)
let data = null;
let container = document.getElementById('container');
let current = 0;

// Function to fetch data.
function loadData() {
	// Create a promise
	return new Promise((resolve, reject) => {
		// Fetch data from 
		fetch('https://jsonplaceholder.typicode.com/posts')
			.then(res => {
				if (!res.ok) {
					// Reject the promise.
					reject(new Error("Response Status: " + res.status));
				} else {
					return res.json();
				}
			}).then(json => {
				data = json;
				// Resolve the promise.
				resolve();
			}).catch(error => {
				// reject the promise.
				reject(error);
			});
	});
}

// Event handler and more (Main loop function that handles most things).
async function main() {
	// If the Promise in loadData() is not resolved correctly, the code under will not be run.
	// Ensuring that there are no unwanted behaviour in the code.
	await loadData();

	// Fill upp initially with some posts (9 posts to start).
	for (let i = 0; i < 9; i++) {
		addNewContent(data[current].title, data[current].body);
	}

	// Event Listener that begins listening only after loadData() is completed.
	window.addEventListener('scroll', () => {
		// Checks if the bottom is visable (before footer).
		if (bottomVisible()) {
			// Adding at most 3 elements each time the bottom is hit 
			for (let i = 0; i < 3; i++) {
				// Ensuring that there are still objects in the json object that
				// can be put the the screen, ensuring that we dont get an indexing error.
				if (container.children.length < data.length) {
					// Adding new Content.
					addNewContent(data[current].title, data[current].body);
				}
			}	
		}
	});
}

// Helper Function that adds new elements to the page.
function addNewContent(heading, text) {
	// Create new element with class "posts".
	const newElement = document.createElement('div');
	newElement.classList.add('posts');

	// Create and add new Header <h4> to newElement.
	const header = document.createElement('h4');
	header.textContent = heading;
	newElement.appendChild(header);

	// Create and add new paragraph <p> to newElement.
	const paragraph = document.createElement('p');
	paragraph.textContent = text;
	newElement.appendChild(paragraph);

	// Append newElement to be the child element of container div.
	container.appendChild(newElement);

	// Count Up current element by 1.
	current++;
}

// Helper Function to check if the bottom of the page is visable
// - 60px to account for the height of the footer.
const bottomVisible = () =>
	document.documentElement.clientHeight + window.scrollY >=
	document.documentElement.scrollHeight - 100;

// Run the main loop function
main();
