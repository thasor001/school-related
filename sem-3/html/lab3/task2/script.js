let input1 = document.getElementById("a");
let input2 = document.getElementById("b");

function swap() {
	let buffer = input1.value;
	input1.value = input2.value;
	input2.value = buffer;
}
