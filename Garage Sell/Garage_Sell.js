document.addEventListener('DOMContentLoaded', function() {
    const ItemInput = document.getElementById("ItemInput");
    const PriceInput = document.getElementById("PriceInput");
    const ItemTable = document.querySelector("#ItemTable tbody");
    const addButton = document.getElementById("addButton");

    function addItem() {
        const Item = ItemInput.value;
        const Price = PriceInput.value;

        if (Item !== "" && Price !== "") {
            let tr = document.createElement('tr');

            let itemTh = document.createElement('th');
            itemTh.classList.add('item');
            itemTh.textContent = Item;

            let priceTh = document.createElement('th');
            priceTh.classList.add('price');
            priceTh.textContent = `$${Price}`;

            const actionTd = document.createElement('td');
            const removeButton = document.createElement('button');
            removeButton.textContent = "x";
            removeButton.addEventListener("click", function() {
                ItemTable.removeChild(tr);
            });

            actionTd.appendChild(removeButton);

            tr.appendChild(actionTd);
            tr.appendChild(itemTh);
            tr.appendChild(priceTh);
            

            ItemTable.appendChild(tr);

            ItemInput.value = '';
            PriceInput.value = '';
        }
    }
    addButton.addEventListener('click', addItem);
});

document.getElementById("printPosterBtn").addEventListener("click", function() {
    // Get the poster content
    var posterContent = document.getElementById("list").innerHTML;
    var originalContent = document.body.innerHTML;

    // Replace page content with poster content
    document.body.innerHTML = posterContent;

    // Open print dialog
    window.print();

    // Restore original page content
    document.body.innerHTML = originalContent;

    // Re-attach event listeners (important after restoring content)
    location.reload();
});
