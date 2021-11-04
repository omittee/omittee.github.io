
const array = [7, 3, 5, 4, 2, 1, 9, 10, 8, 6, 11];
let len = array.length, s;//s是当前索引号
let numAndFake = [];//动态添加元素的数组
let step = [];//保存每次交换步骤
let numArr = [];//保存DOM对象
let auto;//一个计时器


for (let i = 0; i < len; i++) {//动态添加元素
  numAndFake.push('<div class="fake"></div><div class="num" id="id' + i + '"></div>');
}
document.body.innerHTML += numAndFake.join('');

for (let i = 0; i < array.length; i++) {
  numArr[i] = document.getElementById("id" + i);
  numArr[i].innerText = array[i];
  numArr[i].style.backgroundColor = "green";
  numArr[i].style.borderColor = "green";
}


const fake = document.querySelectorAll('.fake');

function origin() {
  for (let i = 0, move = 80, first = 30; i < array.length; i++) {
    numArr[i].style.left = first + i * move + "px";
    numArr[i].style.top = 50 + "px";
  }
  for (let i = 0, width = 1000, hight = 100, head = 50, layer = 1; i < array.length; i++) {
    fake[i].style.top = head + layer * hight + "px";
    fake[i].style.left = width * (i - Math.pow(2, layer - 1) + 2) / parseFloat(Math.pow(2, layer - 1) + 1) + "px";
    if (i == Math.pow(2, layer) - 2) {
      layer++;
    }
  }
}

const build = document.querySelector('.build');
const autoplay = document.querySelector('.autoplay');
const init = document.querySelector('.init');
const pre = document.querySelector('.pre');
const next = document.querySelector('.next');
const end = document.querySelector('.end');
init.addEventListener('click', function () {
  reinit();
});

//建堆动画
build.addEventListener('click', function () {
  origin();//先还原到建堆前
  next.disabled = true;
  pre.disabled = true;
  init.disabled = true;
  build.disabled = true;
  autoplay.disabled = true;
  let temp = 0, t = -1;//用来判断是否初始交换的索引号
  buildSwap = setInterval(function () {
    animateSwap(numArr[temp], fake[temp], true);//真交换，入堆
    if (temp > 0) {
      t = parseInt((temp - 1) / 2);//t是temp的父代
    }
    if (t >= 0 && parseInt(numArr[t].innerText) < parseInt(numArr[temp].innerText)) {
      numArr[t].style.borderColor = "gold";
      numArr[temp].style.borderColor = "gold";
      setTimeout(function () {
        animateSwap(numArr[t], numArr[temp - 1], false);//初始假交换
        numArr[t].style.borderColor = "green";
        numArr[temp - 1].style.borderColor = "green"
      }, 500)
    }
    if (temp == array.length - 1) {//结束入堆
      clearInterval(buildSwap);
      next.disabled = false;
      init.disabled = false;
      autoplay.disabled = false;
      build.disabled = false;
    }
    temp++;
  }, 1200);

})

//自动播放

autoplay.addEventListener('click', function () {
  reinit(false);//初始化
  auto = setInterval(function () {
    next.click();
    if (numArr[0].style.backgroundColor == "lightgreen") {//堆顶变颜色则停止
      clearInterval(auto);
      pre.disabled = false;
      autoplay.disabled = false;
      console.log(step);
    }
  }, 1200);
})
//结束自动播放和建堆

end.addEventListener('click', function () {
  clearInterval(auto);
  clearInterval(buildSwap);
  setTimeout(function () {
    next.disabled = false;
    pre.disabled = false;
    build.disabled = false;
    init.disabled = false;
    reinit();
  }, 500);
})
//初始化
function reinit(flag = true) {//flag判断是否需要回到最初的起点以及是否需要修改数据
  for (let i = 0; i < array.length; i++) {/* 
    numArr[i] = document.getElementById("id" + i); */
    numArr[i].style.backgroundColor = "green";
    numArr[i].style.borderColor = "green";

    if (flag) {
      numArr[i].innerText = array[i];
    }
  }
  len = array.length;
  s = Math.floor(len / 2) - 1;
  counter = 0;
  next.disabled = true;
  pre.disabled = true;
  autoplay.disabled = true;
  step.length = 0;//清空步骤

  if (flag) {
    origin();
  }
  if (!flag) {
    pre.disabled = true;
    next.disabled = false;
    build.disabled = true;
    init.disabled = true;
  }
}
reinit();

pre.addEventListener("click", function () {
  pre.disabled = true;
  let tp1 = step[step.length - 1];
  step.pop();
  let tp2 = step[step.length - 1];
  step.pop();
  if (s <= Math.floor(len / 2) - 1) {
    s++;
  }
  else if (s > Math.floor(len / 2) - 1) {
    s = 0;
  }
  if (tp1 == 0 && tp2 > 2 || tp2 == 0 && tp1 > 2) {
    len++;
  }
  if(tp1<=0&&tp2<=0&&tp1==tp2){
    animateSwap(numArr[-tp1], fake[-tp2], true);
  }
  else{
    animateSwap(numArr[tp1], numArr[tp2], false);
  }
  
  numArr[tp1].style.borderColor = "gold";
  numArr[tp2].style.borderColor = "gold";
  numArr[tp1].style.backgroundColor = "green";
  numArr[tp2].style.backgroundColor = "green";
  setTimeout(function () {
    numArr[tp1].style.borderColor = "green";
    numArr[tp2].style.borderColor = "green";
  }, 500);
  setTimeout(function () {
    pre.disabled = false;
    if (step.length == 0) {
      pre.disabled = true;
      next.disabled = false;
    }
  }, 1100);
})

next.addEventListener("click", function () {
  next.disabled = true;
  if (autoplay.disabled == false) {
    pre.disabled = false;
  }

  heapify(s, ...numArr);

  s--;
  if (s < 0) {
    next.addEventListener("click", topToBottom(fake), false);
    next.removeEventListener("click", topToBottom, false);
    function topToBottom(fake) {

      setTimeout(function () {
        if(len>1){
          animateSwap(numArr[0], numArr[--len], false);
        }
        else if(len==1){
          len--;
        }
        else{
          return;
        }
        step[step.length] = 0;
        step[step.length] = len;

        setTimeout(function () {
        
          numArr[len].style.backgroundColor = "lightgreen";
          numArr[len].style.borderColor = "lightgreen";
          animateSwap(fake[len], numArr[len], true);
          step[step.length++] = -len;
          step[step.length++] = -len;
          
        }, 700);
      }, 500);

      
    }
    s = Math.floor(len / 2) - 1;
  }
  setTimeout(function () {
    next.disabled = false;
    if (numArr[0].style.backgroundColor == "lightgreen") {
      next.disabled = true;
    }
  }, 1100);
})


function heapify(i, ...arr) {
  if (i < 0) {
    return;
  }
  let left = i;
  if (2 * i + 1 < arr.length) {
    left = 2 * i + 1;
  }
  let right = left;
  if (2 * i + 2 < arr.length) {
    right = 2 * i + 2;
  }

  largest = i;
  let arrLeft = parseInt(arr[left].innerText)
  let arrRight = parseInt(arr[right].innerText)
  let arrLarge = parseInt(arr[largest].innerText)

  if (left < len && arrLeft > arrLarge) {
    largest = left;
    arrLarge = parseInt(arr[largest].innerText)//再次更新arrLarge值
  }
  if (right < len && arrRight > arrLarge) {
    largest = right;
    arrLarge = parseInt(arr[largest].innerText)
  }
  arr[i].style.borderColor = "gold";
  arr[largest].style.borderColor = "gold";

  if (largest != i) {
    animateSwap(arr[i], arr[largest], false);
    step[step.length++] = i;
    step[step.length++] = largest;
  }
  setTimeout(function () {
    arr[i].style.borderColor = "green";
    arr[largest].style.borderColor = "green";
  }, 500);
}




function animateSwap(obj1, obj2, flag, callback) {

  const posX1 = obj1.offsetLeft;
  const posY1 = obj1.offsetTop;

  const posX2 = obj2.offsetLeft;
  const posY2 = obj2.offsetTop;

  clearInterval(obj1.timer);
  clearInterval(obj2.timer);

  obj1.timer = setInterval(function () {
    let stepX1 = (posX2 - obj1.offsetLeft) / 10;
    stepX1 = stepX1 > 0 ? Math.ceil(stepX1) : Math.floor(stepX1);

    let stepY1 = (posY2 - obj1.offsetTop) / 10;
    stepY1 = stepY1 > 0 ? Math.ceil(stepY1) : Math.floor(stepY1);

    if (obj1.offsetLeft == posX2 && obj1.offsetTop == posY2) {
      clearInterval(obj1.timer);
      callback && callback();
    }
    obj1.style.left = obj1.offsetLeft + stepX1 + 'px';
    obj1.style.top = obj1.offsetTop + stepY1 + 'px';

  }, 10)

  obj2.timer = setInterval(function () {
    let stepX2 = (posX1 - obj2.offsetLeft) / 10;
    stepX2 = stepX2 > 0 ? Math.ceil(stepX2) : Math.floor(stepX2);
    let stepY2 = (posY1 - obj2.offsetTop) / 10;
    stepY2 = stepY2 > 0 ? Math.ceil(stepY2) : Math.floor(stepY2);
    if (obj2.offsetLeft == posX1 && obj2.offsetTop == posY1) {
      clearInterval(obj2.timer);
      callback && callback();
    }
    obj2.style.left = obj2.offsetLeft + stepX2 + 'px';
    obj2.style.top = obj2.offsetTop + stepY2 + 'px';
  }, 10)

  if (!flag) {//flag控制是否假交换
    window.setTimeout(function () {
      const temp = obj1.innerText;
      obj1.innerText = obj2.innerText;
      obj2.innerText = temp;
      obj1.style.left = posX1 + 'px';
      obj1.style.top = posY1 + 'px';
      obj2.style.left = posX2 + 'px';
      obj2.style.top = posY2 + 'px';
    }, [500]);
  }

}
/* 
function animateSwap(obj1, obj2, flag, callback) {
  const runkeyframes =` @keyframes ball-run{
    to{
        left: 0px;
        top: 0px;
    }
  }`
  const style = document.createElement('style');
  style.innerHTML = runkeyframes;

  document.getElementByTagName('head')[0].appendChild(style);
} */

// heapSort(...numArr);
// [numArr[0],numArr[1],numArr[2],numArr[3],numArr[4],numArr[5],numArr[6]]


