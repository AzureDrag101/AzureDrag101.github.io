document.addEventListener('DOMContentLoaded', function() {
    const itemInput = document.getElementById('itemInput');
    const priceInput = document.getElementById('priceInput');
    const addButton = document.getElementById('addButton');
    const itemList = document.getElementById('itemList');

    // Function to add a new item to the list
    function addItem() {
        const itemText = itemInput.value.trim();
        const priceText = priceInput.value.trim();
        
        if (itemText !== '' && priceText !== '') {
            // Create a new list item
            const li = document.createElement('li');

            // Create the remove button
            const removeButton = document.createElement('button');
            removeButton.textContent = 'Delete';
            removeButton.classList.add('remove-button');
            removeButton.addEventListener('click', function() {
                itemList.removeChild(li);
            });

            // Create the item text element
            const itemSpan = document.createElement('span');
            itemSpan.classList.add('item');
            itemSpan.textContent = itemText;

            // Create the price text element
            const priceSpan = document.createElement('span');
            priceSpan.classList.add('price');
            priceSpan.textContent = `$${priceText}`;

            // Append the remove button, item text, and price to the list item
            li.appendChild(removeButton);
            li.appendChild(itemSpan);
            li.appendChild(priceSpan);

            // Append the list item to the list
            itemList.appendChild(li);

            // Clear the inputs
            itemInput.value = '';
            priceInput.value = '';
        }
    }

    // Add item on button click
    addButton.addEventListener('click', addItem);

    // Add item on pressing Enter key in the item input
    itemInput.addEventListener('keypress', function(event) {
        if (event.key === 'Enter') {
            addItem();
        }
    });

    // Add item on pressing Enter key in the price input
    priceInput.addEventListener('keypress', function(event) {
        if (event.key === 'Enter') {
            addItem();
        }
    });
});

