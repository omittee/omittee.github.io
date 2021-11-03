function animateSwap(obj1, obj2, flag, callback) {
  var posX1 = obj1.offsetLeft;
  var posY1 = obj1.offsetTop;

  var posX2 = obj2.offsetLeft;
  var posY2 = obj2.offsetTop;

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





var array = [7, 3, 5, 4, 2, 1, 9, 10];
var len = array.length, s;
var numAndFake = [];
numAndFake.push('<button class="init">初始化</button><button class="build">建堆</button><button class="autoplay">自动播放</button><button class="pre">上一步</button><button class="next">下一步</button><button class="end">结束</button>')
for (let i = 0; i < len; i++) {
  numAndFake.push('<div class="fake"></div><div class="num" id="id' + i + '"></div>');
}
document.body.innerHTML = numAndFake.join('');
var step = [];//保存每次交换步骤
var numArr = [];//保存DOM对象
var counter = 0, auto;

for (let i = 0; i < array.length; i++) {
  numArr[i] = document.getElementById("id" + i);
  numArr[i].innerText = array[i];
  numArr[i].style.backgroundColor = "green";
  numArr[i].style.borderColor = "green";
}
var fake = document.querySelectorAll('.fake');
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
let build = document.querySelector('.build');
let autoplay = document.querySelector('.autoplay');
let init = document.querySelector('.init');
let pre = document.querySelector('.pre');
let next = document.querySelector('.next');
let end = document.querySelector('.end');
init.addEventListener('click', function () {
  reinit();
});

//建堆动画
build.addEventListener('click', function () {
  origin();
  next.disabled = true;
  pre.disabled = true;
  init.disabled = true;
  build.disabled = true;
  autoplay.disabled = true;
  let temp = 0, t = 0;
  buildSwap = setInterval(function () {
    animateSwap(numArr[temp], fake[temp], true);
    if (temp > 0) {
      t = (temp - 1) / 2;
    }
    if (t > 0 && numArr[t] < numArr[temp]) {
      animateSwap(numArr[t], numArr[temp], false)
    }
    if (temp == array.length - 1) {
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
  reinit(false);
  auto = setInterval(function () {
    next.click();
    if (numArr[0].style.backgroundColor == "lightgreen") {
      clearInterval(auto);
      pre.disabled = false;
      autoplay.disabled = false;
      // console.log(step);
    }
  }, 1200);
})
//结束自动播放和建堆

end.addEventListener('click', function () {
  clearInterval(auto);
  clearInterval(buildSwap);
  setInterval(function () {
    next.disabled = false;
    pre.disabled = false;
    build.disabled = false;
    init.disabled = false;
    reinit();
  }, 500)
})
//初始化
function reinit(flag = true) {//flag判断是否需要回到最初的起点
  for (let i = 0; i < array.length; i++) {
    numArr[i] = document.getElementById("id" + i);
    numArr[i].innerText = array[i];
    numArr[i].style.backgroundColor = "green";
    numArr[i].style.borderColor = "green";
  }
  len = 7;
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
  if (counter > 0) {
    counter--;
  }
  if (s <= Math.floor(len / 2) - 1) {
    s++;
  }
  else if (s > Math.floor(len / 2) - 1) {
    s = 0;
  }
  if (tp1 == 0 && tp2 > 2 || tp2 == 0 && tp1 > 2) {
    len++;
  }
  animateSwap(numArr[tp1], numArr[tp2], false);
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
    next.addEventListener("click", topToBottom(), false);
    next.removeEventListener("click", topToBottom, false);
    function topToBottom() {
      setTimeout(function () {
        animateSwap(numArr[0], numArr[--len], false);
        step[step.length] = 0;
        step[step.length] = len;
      }, 500);
      setTimeout(function () {
        numArr[len].style.backgroundColor = "lightgreen";
        numArr[len].style.borderColor = "lightgreen";
      }, 1000);
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
  let left = 2 * i + 1;
  let right = 2 * i + 2;
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





// heapSort(...numArr);
// [numArr[0],numArr[1],numArr[2],numArr[3],numArr[4],numArr[5],numArr[6]]


