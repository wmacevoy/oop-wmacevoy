// https://mochajs.org/#installation


import {Cord, Equipment} from '../cord.mjs'

// import { assert } from 'assert'
import { assert, expect, should } from 'chai';

describe('Cord', ()=>{
  describe('length', ()=>{
    it('is the first constructor parameter ',()=>{
      const cord = new Cord(1,"male plug",3);
      expect(cord.length).to.equal(1);
    })
    it('can be changed',()=>{
      const cord = new Cord(1,"male plug",3);
      cord.length = 2.5;
      expect(cord.length).to.equal(2.5);
    })
    it('must be positive',()=>{
      const cord = new Cord(1,"male plug",3);
      expect(()=>{cord.length = 0.0})
        .to.throw("length must be positive")
    });
  }); // describe length
  describe('length', ()=>{
    it('is the first constructor parameter ',()=>{
      const cord = new Cord(1,"male plug",3);
      expect(cord.length).to.equal(1);
    })
    it('can be changed',()=>{
      const cord = new Cord(1,"male plug",3);
      cord.length = 2.5;
      expect(cord.length).to.equal(2.5);
    })
    it('must be positive',()=>{
      const cord = new Cord(1,"male plug",3);
      expect(()=>{cord.length = 0.0})
        .to.throw("length must be positive")
    });
  }); // describe length
}); // describe Cord
