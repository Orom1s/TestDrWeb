#pragma once

#include "dict_interface.h"

#include <vector>
#include <algorithm>

template <class Key>
class DictException : public not_found_exception<Key> {
public:

	DictException(const char* message, const Key& key) noexcept : err(message), key_(key) {}

	const Key& get_key() const noexcept override {
		return key_;
	}

	const char* what() const noexcept {
		return err.what();
	}
private:
	Key key_;
	std::exception err;
};

template<class Key, class Value>
class Dict : public dictionary<Key, Value> {
public:
	explicit Dict() = default;

	Dict(Key key, Value value) {
		set(key, value);
	}

	const Value& get(const Key& key) const override {
		auto pos = find_pos(key);
		if (pos != dict.end()) {
			auto [key, val] = *pos;
			return val;
		}
		else {
			throw DictException<Key>{ "Invalid key:", key };
		}
	}
	void set(const Key& key, const Value& value) override {
		dict.push_back(std::make_pair(key, value));
	}
	bool is_set(const Key& key) const override {
		auto pos = find_pos(key);
		if (pos != dict.end()) {
			return true;
		}
		else {
			return false;
		}
	}

private:
	std::vector<std::pair<Key, Value>> dict;

	template <typename It>
	It find_pos(const Key& key) const {
		auto pos = std::find_if(dict.begin(), dict.end(), [&key](auto key_val) {
			return key_val.first == key;
			});
		return pos;
	}
};