// C library API
const ffi = require("ffi-napi");

// Express App (Routes)
const express = require("express");
const app = express();
const path = require("path");

// Minimization
// const fs = require("fs");
// const JavaScriptObfuscator = require("javascript-obfuscator");

// Important, pass in port as in `npm run dev 1234`, do not change
const portNum = process.argv[2];

var p = path.join(__dirname + "/bin/dictionary.dll");
console.log(p);
let treeLib = ffi.Library(p, {
  checkWord: ["int", ["void*", "string", "string"]],
  createTree: ["void*", []],
  freeTree: ["void", ["void*"]],
});

p = path.join(__dirname + "/bin/fileAccess.dll");
console.log(p);
let fileLib = ffi.Library(p, {
  getWordAtIndex: ["string", ["int", "string"]],
});

var root = treeLib.createTree();
process.on("exit", function () {
  console.log("Freeing Tree");
  treeLib.freeTree(root);
});

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

function isLeapYear(year) {
  if (year % 400 == 0) {
    return true;
  }
  if (year % 100 == 0) {
    return false;
  }
  if (year % 4 == 0) {
    return true;
  }
  return false;
}

function convertDate(date) {
  var ar = date.split("-");

  var date1 = new Date(2022, 0, 1, 0, 0, 0, 0);

  var month = parseInt(ar[1]);
  month--;
  if (month >= 0 && month <= 9) {
    month = "0" + month;
  }

  var date2 = new Date(ar[0], month, ar[2], 0, 0, 0, 0);

  var diffMiliseconds = date2.getTime() - date1.getTime();
  var diffDays = Math.ceil(diffMiliseconds / (1000 * 3600 * 24));

  console.log(diffDays);
  return diffDays;
}

app.get("/", function (req, res) {
  res.sendFile(path.join(__dirname + "/public/index.html"));
});

app.get("/styles.css", function (req, res) {
  res.sendFile(path.join(__dirname + "/public/styles.css"));
});

app.get("/reset.css", function (req, res) {
  res.sendFile(path.join(__dirname + "/public/reset.css"));
});

app.get("/index.js", function (req, res) {
  res.sendFile(path.join(__dirname + "/public/index.js"));
});

app.get("/check", function (req, res) {
  var word = req.query.word;
  var date = req.query.date;

  if (!checkDate(date)) {
    res.send({
      word: null,
      state: 0,
    });
  } else {
    var index = convertDate(date);
    var p = path.join(__dirname + "/text/words-medium-random.txt");
    var ans = fileLib.getWordAtIndex(index, p);

    if (ans == null) {
      console.log("Error openning file\n");
      res.send({
        word: null,
        state: 0,
      });
    } else {
      var ret = treeLib.checkWord(root, word, ans);
      console.log("checkWord(" + word + ") = " + ret + "\n");

      res.send({
        word: word,
        state: ret,
      });
    }
  }
});

app.get("/giveup", function (req, res) {
  var date = req.query.date;

  if (!checkDate(date)) {
    res.send({
      word: null,
    });
  } else {
    var index = convertDate(date);
    var p = path.join(__dirname + "/text/words-medium-random.txt");
    var ans = fileLib.getWordAtIndex(index, p);

    res.send({
      word: ans,
    });
  }
});

app.listen(portNum);
console.log("Running app at localhost: " + portNum);
