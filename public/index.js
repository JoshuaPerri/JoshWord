var word = "ta";
var id = 0;
var dictionary = ["A"];

function insertAnswer(guess, a, id) {
  var answers = $(".word-box").eq(a);

  $(answers).append('<label id="' + id + '">' + guess + "<label/>");

  console.log($(answers).children()[0]);

  $(answers)
    .children()
    .each((index, element) => {
      console.log(guess, $(element));
      if (!isAbove(guess, $(element).text())) {
        $("#" + id + "").insertBefore(element);
        console.log(guess, $(element).text());
        return false;
      }
    });
}

// Checks if 'a' is alphabetically before 'b'
function isAbove(a, b) {
  if (a > b) {
    return true;
  } else {
    return false;
  }
}

$("#dark-mode").click(() => {
  var val = Cookies.get("dark");
  console.log(val);
  if (val == undefined) {
    Cookies.set("dark", "1");
  } else if (val == "0") {
    Cookies.set("dark", "1");
  } else {
    Cookies.set("dark", "0");
  }

  toggleDarkMode();
});

function toggleDarkMode() {
  $("body").toggleClass("light dark");
  $("#dark-mode").toggleClass("light dark");
  $("#dark-mode-button").toggleClass("light dark");

  $("#upper-gradient").toggleClass("light dark");
  $("#lower-gradient").toggleClass("light dark");

  $("#info").toggleClass("light dark");
  $("#popup").toggleClass("light dark");
  $("#popup").toggleClass("light dark");
  $("#current-word").toggleClass("light dark");
  $("#date-picker").toggleClass("dark");
  $("#giveup-button").toggleClass("dark");

  $("#popup").toggleClass("light dark");
  $("#exit-button-text").toggleClass("light dark");

  $("#result-exit-button-text").toggleClass("dark");
  $("#result-popup").toggleClass("dark");
}

$("#info").click(() => {
  $("#popup").toggleClass("hidden shown");
});

$("#exit-button").click(() => {
  $("#popup").toggleClass("hidden shown");
});

$("#result-exit-button").click(() => {
  $("#result-popup").toggleClass("hidden shown");
});

function setCurrentDate() {
  var date = new Date();
  var day = date.getDate();
  var month = date.getMonth();
  var year = date.getFullYear();

  if (day >= 1 && day <= 9) {
    day = "0" + day;
  }

  month++;
  if (month >= 1 && month <= 9) {
    month = "0" + month;
  }

  $("#date-picker").val(year + "-" + month + "-" + day);
  $("#date-picker").attr("max", year + "-" + month + "-" + day);
}

function checkDate(pickedDate) {
  var currentDate = new Date();
  var cDay = currentDate.getDate();
  var cMonth = currentDate.getMonth();
  var cYear = currentDate.getFullYear();

  var fDay = 1;
  var fMonth = 1;
  var fYear = 2022;

  cMonth++;

  var ar = pickedDate.split("-");

  if (ar[0] > fYear && ar[0] < cYear) {
    return true;
  }

  if (ar[0] == fYear && ar[0] == cYear) {
    if (ar[1] < cMonth && ar[1] > fMonth) {
      return true;
    }

    if (ar[1] == cMonth && ar[1] == fMonth) {
      if (ar[2] <= cDay && ar[2] >= fDay) {
        return true;
      }
    } else if (ar[1] == cMonth) {
      if (ar[2] <= cDay) {
        return true;
      }
    } else if (ar[1] == fMonth) {
      if (ar[2] >= fDay) {
        return true;
      }
    }
  } else if (ar[0] == fYear) {
    if (ar[1] > fMonth) {
      return true;
    } else if (ar[1] == fMonth) {
      if (ar[2] >= fDay) {
        return true;
      }
    }
  } else if (ar[0] == cYear) {
    if (ar[1] < cMonth) {
      return true;
    } else if (ar[1] == cMonth) {
      if (ar[2] <= cDay) {
        return true;
      }
    }
  }

  return false;
}

function victory(answer) {
  $("#result-title").text("Victory!");

  $("#result-answer-success").text(answer);
  $("#result-guesses").text(id + 1);

  $("#result-success").show();
  $("#result-fail").hide();

  $("#result-popup").toggleClass("hidden shown");
  $("#current-word").prop("disabled", true);
}

function fail(answer) {
  $("#result-title").text("Too bad!");

  $("#result-answer-fail").text(answer);
  $("#result-guesses").text(id + 1);

  $("#result-success").hide();
  $("#result-fail").show();

  $("#result-popup").toggleClass("hidden shown");
  $("#current-word").prop("disabled", true);
}

$(document).ready(() => {
  if (Cookies.get("dark") == "1") {
    toggleDarkMode();
  }

  setCurrentDate();

  $("#date-picker").change((e) => {
    $("#upper-words").empty();
    $("#lower-words").empty();
    $("#current-word").val("");
    $("#current-word").prop("disabled", false);
  });

  $("#exit-button").change((e) => {
    $("#exit-button").toggleClass("shown");
  });

  var waiting = false;
  $("form").submit((e) => {
    e.preventDefault();

    if (waiting) {
      return;
    }
    waiting = true;

    var answer = $("#current-word").val();
    var date = $("#date-picker").val();

    answer = answer.toUpperCase();

    jQuery.ajax({
      type: "get",
      dataType: "json",
      url: "/check",
      data: {
        word: answer,
        date: date,
      },
      success: function (data) {
        console.log("Successfully checked", data.word, data.state);
        var state = data.state;

        switch (state) {
          case 0:
            $("#current-word").removeClass("wrong");
            setTimeout(() => {
              $("#current-word").addClass("wrong");
            }, 10);
            break;
          case 1:
            victory(answer);
            break;
          case 2:
            insertAnswer(answer, 1, id++);
            $("#current-word").val("");
            break;
          case 3:
            insertAnswer(answer, 0, id++);
            $("#current-word").val("");
            break;
        }
        waiting = false;
      },
      fail: function (error) {
        console.log(error);
        console.log("Did not successfully check");
        waiting = false;
      },
    });
  });

  $("#giveup-button").click((e) => {
    e.preventDefault();
    var date = $("#date-picker").val();
    console.log("giveup");

    jQuery.ajax({
      type: "get",
      dataType: "json",
      url: "/giveup",
      data: {
        date: date,
      },
      success: function (data) {
        $("#current-word").val(data.word);
        fail(data.word);
      },
      fail: function (error) {
        console.log(error);
      },
    });
  });
});
