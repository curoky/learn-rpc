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
package test

import (
	"testing"

	"github.com/stretchr/testify/assert"
	thrifter "github.com/thrift-iterator/go"
)

func TestUsage(t *testing.T) {
	// marshal to thrift
	thriftEncodedBytes, err := thrifter.Marshal(1)
	assert.NoError(t, err)

	// unmarshal back
	var val int
	err = thrifter.Unmarshal(thriftEncodedBytes, &val)
	assert.NoError(t, err)
	assert.Equal(t, 1, val)
}