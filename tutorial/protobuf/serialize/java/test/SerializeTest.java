/*
 * Copyright (c) 2018-2022 curoky(cccuroky@gmail.com).
 *
 * This file is part of learn-rpc.
 * See https://github.com/curoky/learn-rpc for further info.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import static org.junit.jupiter.api.Assertions.*;

import com.google.protobuf.Any;
import com.google.protobuf.CodedOutputStream;
import com.google.protobuf.TextFormat;
import com.google.protobuf.util.JsonFormat;
import idl.pb.Types.*;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import org.junit.jupiter.api.Test;

public class SerializeTest {
  ClassType getRequest() {
    ClassType.Builder requestBuilder = ClassType.newBuilder();
    requestBuilder.setVarInt32(1)
        .setVarFloat(2.0f)
        .setVarStr("hello")
        .setVarEnum(ClassType.EnumType.FOUR)
        .addVarInt32Lists(1)
        .setVarInnerClass(ClassType.InnerClassType.newBuilder().setVarBool(false).build());
    // .setVarAny(Any.newBuilder().setTypeUrl("type.googleapis.com/idl.pb.ClassType").build());
    return requestBuilder.build();
  }

  @Test
  public void testSerialize() {
    ClassType request = getRequest();
    ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
    CodedOutputStream output = CodedOutputStream.newInstance(outputStream, 0);
    assertDoesNotThrow(() -> {
      request.writeTo(output);
      output.flush();
    });
    assertEquals(21, outputStream.toString().length());

    // ClassType requestBuilder = ClassType.newBuilder();
    ByteArrayInputStream inputStream = new ByteArrayInputStream(outputStream.toByteArray());
    ClassType.Builder requestNew = ClassType.newBuilder();
    assertDoesNotThrow(() -> { requestNew.mergeFrom(inputStream); });
    assertEquals(request, requestNew.build());
  }

  @Test
  public void jsonFormat() {
    assertDoesNotThrow(() -> {
      JsonFormat.Printer printer = JsonFormat.printer();
      String jsonContent = printer.print(getRequest());
      assertEquals("{\n"
              + "  \"varInt32\": 1,\n"
              + "  \"varFloat\": 2.0,\n"
              + "  \"varStr\": \"hello\",\n"
              + "  \"varEnum\": \"FOUR\",\n"
              + "  \"varInt32Lists\": [1],\n"
              + "  \"varInnerClass\": {\n"
              + "  }\n"
              + "}",
          jsonContent);

      JsonFormat.Parser parser = JsonFormat.parser();
      ClassType.Builder requestBuilder = ClassType.newBuilder();
      parser.merge(jsonContent, requestBuilder);
      ClassType request = requestBuilder.build();
      assertEquals(request, getRequest());
    });
  }

  @Test
  void textFormat() {
    assertDoesNotThrow(() -> {
      TextFormat.Printer printer = TextFormat.printer();
      String jsonContent = printer.printToString(getRequest());
      assertEquals("var_int32: 1\n"
              + "var_float: 2.0\n"
              + "var_str: \"hello\"\n"
              + "var_enum: FOUR\n"
              + "var_int32_lists: 1\n"
              + "var_inner_class {\n"
              + "}\n",
          jsonContent);

      TextFormat.Parser parser = TextFormat.getParser();
      ClassType.Builder requestBuilder = ClassType.newBuilder();
      parser.merge(jsonContent, requestBuilder);
      ClassType request = requestBuilder.build();
      assertEquals(request, getRequest());
    });
  }
}
