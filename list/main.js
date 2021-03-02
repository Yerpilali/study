function addTask() {
    let input = document.querySelector('.input');
    let list = document.querySelector('.list'); 
    if(input.value == "") {
        alert("Введите задачу");
    }

    else{
        let li = document.createElement('li');
            li.className = 'task';
            list.appendChild(li)
        let checkbox = document.createElement('input');
            checkbox.type = 'checkbox';
            checkbox.className = 'checkbox';
            checkbox.addEventListener('change', checkTask);
        let text = document.createElement('div');
            text.textContent = input.value;
            text.className = 'text';
        let delbtn = document.createElement('button');
            delbtn.className = 'delBtn';
            delbtn.textContent = 'X';
            delbtn.addEventListener('click', delTask);
        li.appendChild(checkbox);
        li.appendChild(text);
        li.appendChild(delbtn);
    } 
}

function delTask({target}){
    target.closest('.task').remove();
}

function checkTask({target}){
    let text = target.closest('.task').querySelector('.text');
    text.classList.add('done');
    target.remove();
}