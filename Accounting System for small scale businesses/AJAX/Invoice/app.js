

document.querySelector('#btn1').addEventListener('click', getCustomer);
document.querySelector('#btn2').addEventListener('click', getCustomers);


// one Customer

function getCustomer() {
    let xhr = new XMLHttpRequest();
    xhr.open('GET', 'customer.json', true);

    xhr.onload = function() {
        if(xhr.status === 200) {
            console.log(xhr.responseText);

            const customer = JSON.parse(xhr.responseText);



            let table = document.createElement("table");
            let tableHeader = table.insertRow(0);
            tableHeader.innerHTML = "<th>ID</th> <th>Name</th> <th>Invoice No.  </th> <th>Amount    </th> <th>Transaction   </th>";
            let tableRow = table.insertRow();
            tableRow.innerHTML = `<td>${customer.id}</td>   <td>${customer.name}</td>   <td>${customer.company}</td>   <td>${customer.phone}</td>   <td>${customer.bankName}</td>`;

            document.querySelector('#customer').append(table);

        }
    };



    xhr.send();
}


// all Customers

function getCustomers() {
    let xhr = new XMLHttpRequest();
    xhr.open('GET', 'customers.json', true);

    xhr.onload = function() {
        if(xhr.status === 200) {
            console.log(xhr.responseText);
            const customers = JSON.parse(xhr.responseText);

            let table = document.createElement("table");
            let tableHeader = table.insertRow(0);
            tableHeader.innerHTML = "<th>ID    </th> <th>     Name    </th> <th>     Invoice No.   </th> <th>Amount    </th> <th> Transaction   </th>";

            customers.forEach(function (customer) {
                let tableRow = table.insertRow();
                tableRow.innerHTML = `<td>${customer.id}</td>   <td>${customer.name}</td>   <td>${customer.company}</td>   <td>${customer.phone}</td>   <td>${customer.bankName}</td>`;

            });


            document.querySelector('#customers').append(table);  

        }
    };

    xhr.send();
}
