/* Address: CODE:a934; name: FUN_CODE_a934; body bytes: 25 */

undefined1 FUN_CODE_a934(undefined1 *param_1,undefined1 param_2,char param_3)

{
  if (param_3 == '\x01') {
    return *(undefined1 *)CONCAT11(param_2,param_1);
  }
  if (param_3 == '\0') {
    return *param_1;
  }
  if (param_3 == -2) {
    return *(undefined1 *)ZEXT12(param_1);
  }
  return *(undefined1 *)CONCAT11(param_2,param_1);
}

