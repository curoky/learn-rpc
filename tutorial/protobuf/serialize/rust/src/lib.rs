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


#[cfg(test)]
mod tests {

    use protobuf::Message;
    use types::ClassType;

    #[test]
    fn test_serialize() {
        let mut req = ClassType::new();
        req.var_int64 = 1;
        req.var_double = 2.0;

        // debug string
        assert_eq!(req.to_string(), "var_int64: 1 var_double: 2");

        // text string
        assert_eq!(
            protobuf::text_format::print_to_string(&req),
            "var_int64: 1 var_double: 2"
        );
        assert_eq!(
            protobuf::text_format::print_to_string_pretty(&req),
            "var_int64: 1\nvar_double: 2\n"
        );

        // json string
        let json_string = protobuf_json_mapping::print_to_string(&req).unwrap();
        assert_eq!(json_string, r#"{"varInt64": "1", "varDouble": 2.0}"#);

        // binary
        let serialized = req.write_to_bytes().unwrap();

        let req2 = ClassType::parse_from_bytes(&serialized).unwrap();
        assert_eq!(req2.var_int64, 1);
        assert_eq!(req2.var_double, 2.0);
    }
}
