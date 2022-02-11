// https://mochajs.org/#installation


import {Cord, Equipment} from '../cord.mjs'

// import { assert } from 'assert'
import { assert, expect, should } from 'chai';

describe('Cord', ()=>{
  describe('length', ()=>{
    it('is the first constructor parameter ',()=>{
      const cord = new Cord(1,"male plug",3);
      assert(cord.length,1);
    })
    it('can be changed',()=>{
      const cord = new Cord(1,"male plug",3);
      cord.length = 2.5;
      assert(cord.length,2.5);
    })
    it('must be positive',()=>{
      const cord = new Cord(1,"male plug",3);
      expect(()=>{cord.length = 0.0;})
        .to.throw("length must be positive")
    });
  });
});

describe('Array', function() {
  describe('#indexOf()', function() {
    it('should return -1 when the value is not present', function() {
      assert([1, 2, 3].indexOf(4),-1);
    });
  });
});
