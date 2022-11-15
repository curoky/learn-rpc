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

import idl.thrift.*;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import org.apache.thrift.TDeserializer;
import org.apache.thrift.TSerializer;
import org.apache.thrift.protocol.TBinaryProtocol;
import org.apache.thrift.protocol.TSimpleJSONProtocol;
import org.junit.jupiter.api.Test;

public class MainTest {
  @Test
  public void basicUsage() {
    assertEquals(typesConstants.GLOBAL_CONST_VAR_STRING, "123");

    // enum
    EnumType enumType = EnumType.ONE;
    assertEquals(enumType.getValue(), 1);
    assertEquals(EnumType.findByValue(0), EnumType.ZERO);

    // union
    UnionType unionType = UnionType.var_i32(0);
    assertTrue(unionType.isSetVar_i32());
    assertFalse(unionType.isSetVar_i16());
    unionType.setVar_i16((short) 0);
    assertFalse(unionType.isSetVar_i32());
    assertTrue(unionType.isSetVar_i16());

    // struct
    StructType structType = new StructType();
    structType.setVar_bool(false);
    assertTrue(structType.isSetVar_bool());
    assertFalse(structType.isSetVar_i32());
    structType.setVar_string_list(Arrays.asList("a", "b", "c"));
    structType.setVar_string_set(null);
    // structType.setVar_required_i32(0);
    structType.setVar_optional_i32(0);

    // serialize debug string
    assertEquals(structType.toString(),
        "StructType(var_bool:false, var_byte:0, var_i16:0, var_i32:0, var_i64:0, var_double:0.0, var_string:null, var_binary:null, var_string_type:null, var_string_list:[a, b, c], var_binary_list:null, var_string_set:null, var_string_binary_map:null, var_enum:null, var_enum_set:null, var_union:null, var_required_i32:0, var_optional_i32:0)");

    // serialize binary string
    assertDoesNotThrow(() -> {
      TSerializer serializer = new TSerializer(new TBinaryProtocol.Factory());
      byte[] content = serializer.serialize(structType);
      TDeserializer deserializer = new TDeserializer(new TBinaryProtocol.Factory());

      StructType structType2 = new StructType();
      deserializer.deserialize(structType2, content);
      assertEquals(structType, structType2);
    });

    // serialize json string
    assertDoesNotThrow(() -> {
      TSerializer serializer = new TSerializer(new TSimpleJSONProtocol.Factory());
      assertEquals(serializer.toString(structType),
          "{\"var_bool\":0,\"var_byte\":0,\"var_i16\":0,\"var_i32\":0,\"var_i64\":0,\"var_double\":0.0,\"var_string_list\":[\"a\",\"b\",\"c\"],\"var_required_i32\":0,\"var_optional_i32\":0}");
    });
  }
}
