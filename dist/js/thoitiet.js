Get_Thoitiet();

function Get_Thoitiet() {

    const arr = ["Chủ Nhật", "Thứ Hai", "Thứ Ba", "Thứ Tư", "Thứ Năm", "Thứ Sáu", "Thứ Bảy"];
    const today = new Date();
    const h = today.getHours();
    const m = checkTime(today.getMinutes());
    const s = checkTime(today.getSeconds());
    const day = arr[today.getDay()];
    const date = checkTime(today.getDate());
    const year = today.getFullYear();
    const month = checkTime(today.getMonth()+1);function checkTime(i) {
    if (i < 10) i = "0" + i;  
        return i;
    }

    // document.getElementById('clock').innerHTML =  h + ":" + m + ":" + s;
    document.getElementById('ngayhientai').innerHTML = day + ", " + date +"."+month+"."+year;


    const xhttpr = new XMLHttpRequest();
    xhttpr.open('GET', 'https://api.openweathermap.org/data/2.5/weather?q=Vinh Long&appid=5a383cdee3d0e7e579889741686fae8f&&units=metric', true);
    
    xhttpr.send();
    
    xhttpr.onload = ()=> {
        if (xhttpr.status === 200) {
            const response = JSON.parse(xhttpr.response);

            document.getElementById('giatrinhietdo').textContent = Math.round(response.main.feels_like*10)/10+"°C";
            document.getElementById('trangthaithoitiet').textContent = response.weather[0].description;
            document.getElementById('trangthaithoitiet').textContent = response.weather[0].description;
            document.getElementById('nhietdongay').textContent = "Độ ẩm " + response.main.humidity + "%";

            switch (response.weather[0].main){

                case "Clear": 
                    document.getElementById("iconthoitiet").src = "/IOT/dist/img/Thoitiet/iconthoitiet_nang.png";
                    document.getElementById('thoitiet').setAttribute("style", "background-image: url('dist/img/Thoitiet/nang.jpg')")
                    break;
                case "Clouds": 
                    document.getElementById("iconthoitiet").src = "/IOT/dist/img/Thoitiet/iconthoitiet_may.png";
                    document.getElementById('thoitiet').setAttribute("style", "background-image: url('dist/img/Thoitiet/may.jpg')")
                    break;
                case "Rain": 
                    document.getElementById("iconthoitiet").src = "/IOT/dist/img/Thoitiet/iconthoitiet_mua.png";
                    document.getElementById('thoitiet').setAttribute("style", "background-image: url('dist/img/Thoitiet/mua.jpg')")
                    break;
                // thay doi
                default: 
                    document.getElementById("iconthoitiet").src = "/IOTdist/img/Thoitiet/iconthoitiet_nang.png";
                    document.getElementById('thoitiet').setAttribute("style", "background-image: url('dist/img/Thoitiet/nang.jpg')")
                    break; 
            }

            console.log(response.weather[0].main)
        } else {
            console.log("LOAD WEATHERS ERRO");
        }
    };
    
  setTimeout(startTime, 1000);
}