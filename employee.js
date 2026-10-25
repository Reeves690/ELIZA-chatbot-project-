// Vite passes anything starting with /api along to the backend
const API_URL = "/api";

// ===================================================================
// SAMPLE DATA
// The employee shift API (WBS 3.2.4) is not built yet, so this page
// uses sample shifts for the logged-in employee. When 3.2.4 is done,
// replace the two functions in the "DATA FUNCTIONS" section with
// fetch() calls; nothing else on this page needs to change.
//
// Employees should only see weeks the manager has published (3.2.5),
// so the sample data marks last week, this week and next week as
// published, and the week after that as not published yet.
// ===================================================================

const sampleShifts = [];
const samplePublishedWeeks = [];

function createSampleData() {
  const thisMonday = getMonday(new Date());

  // [dayOffset (0 = Monday), start, end, position]
  const weeklyPattern = [
    [0, "09:00", "17:00", "Cashier"],
    [2, "09:00", "17:00", "Cashier"],
    [3, "14:00", "22:00", "Stock"],
    [5, "10:00", "16:00", "Cashier"]
  ];

  // Weeks -1, 0 and 1 are published
  for (let week = -1; week <= 1; week++) {
    const monday = addDays(thisMonday, week * 7);
    samplePublishedWeeks.push(toDateString(monday));

    for (const [dayOffset, start, end, position] of weeklyPattern) {
      // Skip one shift in some weeks so they don't all look identical
      if (week === 1 && dayOffset === 3) continue;
      sampleShifts.push({
        id: sampleShifts.length + 1,
        date: toDateString(addDays(monday, dayOffset)),
        start: start,
        end: end,
        position: position
      });
    }
  }
}

// ===================================================================
// DATA FUNCTIONS (swap these for real API calls in 3.2.4)
// ===================================================================

// Returns { published: true/false, shifts: [...] } for the week starting on monday.
// If the week isn't published, the employee gets no shifts for it.
async function getMyWeek(monday) {
  const key = toDateString(monday);
  if (!samplePublishedWeeks.includes(key)) {
    return { published: false, shifts: [] };
  }

  const last = toDateString(addDays(monday, 6));
  const shifts = sampleShifts.filter(function (shift) {
    return shift.date >= key && shift.date <= last;
  });
  return { published: true, shifts: shifts };
}

// Returns the employee's next shift (one that hasn't ended yet), or null
async function getMyNextShift() {
  const now = new Date();
  const upcoming = sampleShifts
    .filter(function (shift) { return shiftEndDate(shift) > now; })
    .sort(function (a, b) { return shiftStartDate(a) - shiftStartDate(b); });
  return upcoming.length > 0 ? upcoming[0] : null;
}

// ===================================================================
// DATE HELPERS
// ===================================================================

const DAY_NAMES = ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"];

// Returns the Monday of the week that contains the given date
function getMonday(date) {
  const result = new Date(date.getFullYear(), date.getMonth(), date.getDate());
  const day = result.getDay(); // 0 = Sunday, 1 = Monday, ...
  const diff = day === 0 ? -6 : 1 - day;
  result.setDate(result.getDate() + diff);
  return result;
}

function addDays(date, days) {
  const result = new Date(date);
  result.setDate(result.getDate() + days);
  return result;
}

// Turns a date into "YYYY-MM-DD" using local time (not UTC)
function toDateString(date) {
  const month = String(date.getMonth() + 1).padStart(2, "0");
  const day = String(date.getDate()).padStart(2, "0");
  return date.getFullYear() + "-" + month + "-" + day;
}

// "2026-10-26" + "09:00" -> a Date object in local time
function makeDate(dateString, time) {
  const d = dateString.split("-");
  const t = time.split(":");
  return new Date(Number(d[0]), Number(d[1]) - 1, Number(d[2]), Number(t[0]), Number(t[1]));
}

function shiftStartDate(shift) {
  return makeDate(shift.date, shift.start);
}

function shiftEndDate(shift) {
  return makeDate(shift.date, shift.end);
}

function toMinutes(time) {
  const parts = time.split(":");
  return Number(parts[0]) * 60 + Number(parts[1]);
}

function shiftHours(shift) {
  return (toMinutes(shift.end) - toMinutes(shift.start)) / 60;
}

// "14:00" -> "2:00 PM"
function formatTime(time) {
  let hours = Number(time.split(":")[0]);
  const minutes = time.split(":")[1];
  const suffix = hours >= 12 ? "PM" : "AM";
  hours = hours % 12;
  if (hours === 0) hours = 12;
  return hours + ":" + minutes + " " + suffix;
}

function formatShortDate(date) {
  return date.toLocaleDateString("en-US", { month: "short", day: "numeric" });
}

// ===================================================================
// PAGE STATE
// ===================================================================

let currentMonday = getMonday(new Date());

// ===================================================================
// LOGIN CHECK
// Only logged-in employees may see this page.
// ===================================================================

function goToLogin() {
  localStorage.removeItem("token");
  localStorage.removeItem("role");
  window.location.href = "index.html";
}

function logout() {
  goToLogin();
}

function showBanner(text) {
  const banner = document.getElementById("banner");
  banner.textContent = text;
  banner.classList.remove("hidden");
}

// Managers aren't allowed here, so send them back without logging them out
function stopNonEmployee() {
  window.location.href = "index.html";
  return false;
}

async function checkLogin() {
  const token = localStorage.getItem("token");
  if (!token) {
    goToLogin();
    return false;
  }

  try {
    // Ask the backend who this token belongs to
    const response = await fetch(API_URL + "/auth/me", {
      headers: { Authorization: "Bearer " + token }
    });

    if (response.status === 401) {
      // Token is missing, wrong, or expired
      goToLogin();
      return false;
    }

    if (!response.ok) {
      showBanner("Could not connect to the server. Some information may be out of date.");
      return localStorage.getItem("role") === "employee" || stopNonEmployee();
    }

    const user = await response.json();
    if (user.role !== "employee") {
      return stopNonEmployee();
    }

    document.getElementById("userEmail").textContent = user.email;
    return true;
  } catch (error) {
    // Backend is off; still allow the page to load from what was saved at login
    showBanner("Could not connect to the server. Some information may be out of date.");
    return localStorage.getItem("role") === "employee" || stopNonEmployee();
  }
}

// ===================================================================
// DRAWING THE PAGE
// ===================================================================

async function drawNextShift() {
  const shift = await getMyNextShift();
  const when = document.getElementById("nextShiftWhen");
  const detail = document.getElementById("nextShiftDetail");

  if (!shift) {
    when.textContent = "No upcoming shifts";
    detail.textContent = "";
    return;
  }

  const start = shiftStartDate(shift);
  const now = new Date();
  const todayString = toDateString(now);
  const tomorrowString = toDateString(addDays(now, 1));

  let dayText;
  if (start <= now) {
    dayText = "Now";
  } else if (shift.date === todayString) {
    dayText = "Today";
  } else if (shift.date === tomorrowString) {
    dayText = "Tomorrow";
  } else {
    dayText = start.toLocaleDateString("en-US", { weekday: "long", month: "short", day: "numeric" });
  }

  when.textContent = dayText + ", " + formatTime(shift.start) + " – " + formatTime(shift.end);
  detail.textContent = (shift.position ? shift.position + " · " : "") + shiftHours(shift) + " hours";
}

async function loadWeek() {
  const week = await getMyWeek(currentMonday);

  // Week label
  const sunday = addDays(currentMonday, 6);
  document.getElementById("weekLabel").textContent =
    "Week of " + formatShortDate(currentMonday) + " – " + formatShortDate(sunday) + ", " + sunday.getFullYear();

  // Not published: show the message and hide the list
  document.getElementById("notPublished").classList.toggle("hidden", week.published);
  document.getElementById("dayList").classList.toggle("hidden", !week.published);

  // Summary cards
  let totalHours = 0;
  const workDays = [];
  for (const shift of week.shifts) {
    totalHours += shiftHours(shift);
    if (!workDays.includes(shift.date)) workDays.push(shift.date);
  }
  document.getElementById("statShifts").textContent = week.published ? week.shifts.length : "–";
  document.getElementById("statHours").textContent = week.published ? totalHours : "–";
  document.getElementById("statDaysOff").textContent = week.published ? 7 - workDays.length : "–";

  if (week.published) {
    drawDayList(week.shifts);
  }
}

function drawDayList(shifts) {
  const list = document.getElementById("dayList");
  list.innerHTML = "";
  const todayString = toDateString(new Date());

  for (let i = 0; i < 7; i++) {
    const date = addDays(currentMonday, i);
    const dateString = toDateString(date);

    const row = document.createElement("div");
    row.className = "day-row" + (dateString === todayString ? " today" : "");

    // Left side: day name and date
    const nameBox = document.createElement("div");
    nameBox.className = "day-name";
    const dayName = document.createElement("strong");
    dayName.textContent = DAY_NAMES[i];
    const dayDate = document.createElement("span");
    dayDate.textContent = formatShortDate(date);
    nameBox.appendChild(dayName);
    nameBox.appendChild(dayDate);
    if (dateString === todayString) {
      const tag = document.createElement("span");
      tag.className = "today-tag";
      tag.textContent = "Today";
      nameBox.appendChild(document.createElement("br"));
      nameBox.appendChild(tag);
    }
    row.appendChild(nameBox);

    // Right side: that day's shifts, or "Day off"
    const shiftsBox = document.createElement("div");
    shiftsBox.className = "day-shifts";

    const dayShifts = shifts
      .filter(function (s) { return s.date === dateString; })
      .sort(function (a, b) { return a.start.localeCompare(b.start); });

    if (dayShifts.length === 0) {
      const off = document.createElement("div");
      off.className = "day-off";
      off.textContent = "Day off";
      shiftsBox.appendChild(off);
    }

    for (const shift of dayShifts) {
      const box = document.createElement("div");
      box.className = "shift";

      const left = document.createElement("div");
      const time = document.createElement("span");
      time.className = "shift-time";
      time.textContent = formatTime(shift.start) + " – " + formatTime(shift.end);
      left.appendChild(time);
      if (shift.position) {
        const position = document.createElement("span");
        position.className = "shift-position";
        position.textContent = shift.position;
        left.appendChild(position);
      }

      const hours = document.createElement("span");
      hours.className = "shift-hours";
      hours.textContent = shiftHours(shift) + " hrs";

      box.appendChild(left);
      box.appendChild(hours);
      shiftsBox.appendChild(box);
    }

    row.appendChild(shiftsBox);
    list.appendChild(row);
  }
}

// ===================================================================
// WEEK NAVIGATION
// ===================================================================

function changeWeek(direction) {
  currentMonday = addDays(currentMonday, direction * 7);
  loadWeek();
}

function goToThisWeek() {
  currentMonday = getMonday(new Date());
  loadWeek();
}

// ===================================================================
// START
// ===================================================================

async function start() {
  const allowed = await checkLogin();
  if (!allowed) return;

  createSampleData();
  await drawNextShift();
  await loadWeek();
}

start();
