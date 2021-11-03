function animateSwap(obj1,obj2,callback){
  var posX1=obj1.offsetLeft;
  var posY1=obj1.offsetTop;

  var posX2=obj2.offsetLeft;
  var posY2=obj2.offsetTop;

  clearInterval(obj1.timer);
  clearInterval(obj2.timer);

  obj1.timer=setInterval(function(){
    
    var stepX1=(posX2-obj1.offsetLeft)/10;
    stepX1=stepX1>0?Math.ceil(stepX1):Math.floor(stepX1);
    
    var stepY1=(posY2-obj1.offsetTop)/10;
    stepY1=stepY1>0?Math.ceil(stepY1):Math.floor(stepY1);
    
    if(obj1.offsetLeft==posX2&&obj1.offsetTop==posY2)
    {
      clearInterval(obj1.timer);
      callback&&callback();
    }
    obj1.style.left=obj1.offsetLeft+stepX1+'px';
    obj1.style.top=obj1.offsetTop+stepY1+'px';
    
  },10)

  obj2.timer=setInterval(function(){
    var stepX2=(posX1-obj2.offsetLeft)/10;
    stepX2=stepX2>0?Math.ceil(stepX2):Math.floor(stepX2);
    
    var stepY2=(posY1-obj2.offsetTop)/10;
    stepY2=stepY2>0?Math.ceil(stepY2):Math.floor(stepY2);
    if(obj2.offsetLeft==posX1&&obj2.offsetTop==posY1)
    {
      clearInterval(obj2.timer);
      callback&&callback();
    }

    obj2.style.left=obj2.offsetLeft+stepX2+'px';
    obj2.style.top=obj2.offsetTop+stepY2+'px';
  },10)

  window.setTimeout(function(){
    var temp=obj1.innerText;
    obj1.innerText=obj2.innerText;
    obj2.innerText=temp;
    obj1.style.left=posX1+'px';
    obj1.style.top=posY1+'px';
    obj2.style.left=posX2+'px';
    obj2.style.top=posY2+'px';
  },[500]);
  
}





var array=[7,3,5,4,2,1,9];
var len=array.length,s;
var step=[];//保存每次交换步骤
var numArr=[];//保存DOM对象
var counter=0,auto;

var fake=document.querySelectorAll('.fake');
for(var i=0,move=80,first=30;i<len;i++){
  fake[i].style.left=first+i*move+"px";
}
var init=document.querySelector('.init');
var pre=document.querySelector('.pre');
var next=document.querySelector('.next');
init.addEventListener('click',function(){
  reinit();
});
//自动播放
var autoplay=document.querySelector('.autoplay');
autoplay.addEventListener('click',function(){
  reinit();
  auto=setInterval(function(){
    next.click();
    counter++;
    if(counter==15){
      clearInterval(auto);
      counter=0;
      console.log(step);
    }
  },1200);
})
//结束自动播放
var end=document.querySelector('.end');
end.addEventListener('click',function(){
  clearInterval(auto);
  reinit();
})
//初始化
function reinit(){
  for(var i=0;i<array.length;i++){
    numArr[i]=document.getElementById("id"+i);
    numArr[i].innerText=array[i];
    numArr[i].style.backgroundColor="green";
    numArr[i].style.borderColor="green";
  }
  len=7;
  s=Math.floor(len/2)-1;
  counter=0;
  next.disabled=false;
  pre.disabled=false;
  step.length=0;//清空步骤
}
reinit();

pre.addEventListener("click",function(){
  pre.disabled=true;
  var tp1=step[step.length-1];
  step.pop();
  var tp2=step[step.length-1];
  step.pop();
  if(counter>0){
    counter--;
  }
  if(s<=Math.floor(len/2)-1){
    s++;
  }
  else if(s>Math.floor(len/2)-1){
    s=0;
  }
  if(tp1==0&&tp2>2||tp2==0&&tp1>2){
    len++;
  }
  animateSwap(numArr[tp1],numArr[tp2]);
  numArr[tp1].style.borderColor="gold";
  numArr[tp2].style.borderColor="gold";
  numArr[tp1].style.backgroundColor="green";
  numArr[tp2].style.backgroundColor="green";
  setTimeout(function(){
    numArr[tp1].style.borderColor="green";
    numArr[tp2].style.borderColor="green";
  },500);
  setTimeout(function(){
    pre.disabled=false;
    if(step.length==0){
      pre.disabled=true;
    }
  },1100);
})

next.addEventListener("click",function(){
  next.disabled=true;
  pre.disabled=false;
  heapify(s,...numArr);
  s--;
  if(s<0){
    next.addEventListener("click",topToBottom(),false);
    next.removeEventListener("click",topToBottom,false);
    function topToBottom(){
      setTimeout(function(){
        animateSwap(numArr[0],numArr[--len]);
        step[step.length]=0;
        step[step.length]=len;
      },500);
      setTimeout(function(){
        numArr[len].style.backgroundColor="lightgreen";
        numArr[len].style.borderColor="lightgreen";
      },1000);
    }
    
    s=Math.floor(len/2)-1;
  }
  setTimeout(function(){
    next.disabled=false;
    if(counter==15){
      next.disabled=true;
    }
  },1100);
  
})


function heapify(i,...arr){
  var left=2*i+1;
  var right=2*i+2;
  largest=i;
  var arrLeft=parseInt(arr[left].innerText)
  var arrRight=parseInt(arr[right].innerText)
  var arrLarge=parseInt(arr[largest].innerText)
  
  if(left<len&&arrLeft>arrLarge){
    largest=left;
    arrLarge=parseInt(arr[largest].innerText)//再次更新arrLarge值
  }
  if(right<len&&arrRight>arrLarge){
    largest=right;
    arrLarge=parseInt(arr[largest].innerText)
  }
  arr[i].style.borderColor="gold";
  arr[largest].style.borderColor="gold";

  if(largest!=i){
    animateSwap(arr[i],arr[largest]);
    step[step.length++]=i;
    step[step.length++]=largest;
  }
  setTimeout(function(){
    arr[i].style.borderColor="green";
    arr[largest].style.borderColor="green";
  },500);
}




// heapSort(...numArr);
// [numArr[0],numArr[1],numArr[2],numArr[3],numArr[4],numArr[5],numArr[6]]


