import { describe, it } from "node:test";
import jp from "../src/index";

describe("Tests for Julian Period", () => {
  // NOTE : BC or BCE 4713 = -4712
  it("Should JD and JDN equal to 0 at the start of Julian Period,1 January 4713 BCE,12:00 UTC", (t) => {
    const result = jp.gregorianToJD({
      year: -4712,
      month: 1,
      day: 1,
      hour: 12,
      minute: 0,
      second: 0,
    });
    const expected = { julianDay: 0, julianDayNumber: 0 };
    t.assert.deepEqual(result, expected);
  });
  it("Should return start of Julian Period,1 January 4713 BCE,12:00 UTC when JD or JDN equal to 0", (t) => {
    const result = jp.jdToGregorian(0);
    const expected = {
      year: -4712,
      month: 1,
      day: 1,
      hour: 12,
      minute: 0,
      second: 0,
    };
    t.assert.deepEqual(result, expected);
  });
  // Why Joseph Justus Scaliger's Julian Period started at 1 January 4713 BCE ->
  // the value of cycles were all 1.
  it("Should Solar Number equal to 1, at the start of Julian Period", (t) => {
    const result = jp.solarNumber(-4712);
    const expected = 1;
    t.assert.deepEqual(result, expected);
  });
  it("Should Lunar Number equal to 1, at the start of Julian Period", (t) => {
    const result = jp.lunarNumber(-4712);
    const expected = 1;
    t.assert.deepEqual(result, expected);
  });
  it("Should Indiction Number equal to 1, at the start of Julian Period", (t) => {
    const result = jp.indictionNumber(-4712);
    const expected = 1;
    t.assert.deepEqual(result, expected);
  });
  // Why length of Joseph Justus Scaliger's Julian Period is 7980 years ->
  // the value of cycles will all 1  15×19×28=7980 years later, in CE 3268.
  it("Should Solar Number equal to 1, at the end of Julian Period", (t) => {
    const result = jp.solarNumber(-4712 + 7980);
    const expected = 1;
    t.assert.deepEqual(result, expected);
  });
  it("Should Lunar Number equal to 1, at the end of Julian Period", (t) => {
    const result = jp.lunarNumber(-4712 + 7980);
    const expected = 1;
    t.assert.deepEqual(result, expected);
  });
  it("Should Indiction Number equal to 1, at the end of Julian Period", (t) => {
    const result = jp.indictionNumber(-4712 + 7980);
    const expected = 1;
    t.assert.deepEqual(result, expected);
  });
});

describe("Gregorian Date to JD and JDN", () => {
  // All tests are as of UTC
  it("Should convert a Gregorian date to Julian Day Number (JDN) and Julian Day (JD)", (t) => {
    const inputDate: jp.GregorianDateTime = {
      year: 2022,
      month: 1,
      day: 1,
      hour: 12,
      minute: 0,
      second: 0,
    };

    const result = jp.gregorianToJD(inputDate);
    t.assert.deepEqual(result.julianDay, 2459581);
    t.assert.deepEqual(result.julianDayNumber, 2459581);
  });
});
